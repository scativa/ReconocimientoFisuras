#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <torch/torch.h>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/imgcodecs.hpp>
//using namespace cv;

using namespace std;

class FileManager {
private:
    void convertToLE(uint32_t& value)
    {
        auto aux =
            (((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) << 8) |
                ((value & 0x00FF0000) >> 8) |
                ((value & 0xFF000000) >> 24));
        value = aux;
    }

protected:
    ifstream file[4];
    uint8_t* ptr_train_image;
    uint8_t* ptr_train_image_labels;
    uint8_t* ptr_test_image;
    uint8_t* ptr_test_image_labels;
public:
    static string   m_folder_name;
    static string   m_file_name[];
    static const uint32_t m_number_of_train_images = 60000;
    static const uint32_t m_number_of_test_images = 10000;
    static const uint32_t m_image_row_size = 28;
    static const uint32_t m_image_col_size = 28;
    static const uint32_t m_size_of_image = m_image_row_size * m_image_col_size;
    enum READ_FILE_METHOD { ALL, CHUNK };

    FileManager(const string& PATH = "./data/") {
        m_folder_name = PATH;

        for (size_t idx = 0; idx < 4; idx++) {
            file[idx].open((m_folder_name + m_file_name[idx]).c_str(), ios::binary);
            if (!file[idx]) {
                std::cout << "Unable to open file " << m_file_name[idx] << endl;
                exit(-1);
            }
        }
    }
    bool IsFileFormatValid() {
        // <IsFileFormatValid> 
        // EL formato de los archivos que se bajan de internet del MNIST tienen unos encabezados "medio raros".
        // Esta funcion lee los encabezados de cada archivo y verifica que este todo en orden.
        uint32_t magic, num, nr, nc, num2, num3, num4;

        file[0].read((char*)&magic, sizeof(magic));  convertToLE(magic);
        file[0].read((char*)&num, sizeof(num));  convertToLE(num);
        file[0].read((char*)&nr, sizeof(nr));  convertToLE(nr);
        file[0].read((char*)&nc, sizeof(nc));  convertToLE(nc);
        if (magic != 2051 || num != 60000 || nr != 28 || nc != 28) {
            std::cout << "MNIST data files " << m_file_name[0] << " are corrupted." << endl;
            return false;
        }

        file[1].read((char*)&magic, sizeof(magic));  convertToLE(magic);
        file[1].read((char*)&num2, sizeof(num2));  convertToLE(num2);
        if (magic != 2049 || num2 != 60000) {
            std::cout << "MNIST data files " << m_file_name[1] << " are corrupted." << endl;
            return false;
        }

        file[2].read((char*)&magic, sizeof(magic)); convertToLE(magic);
        file[2].read((char*)&num3, sizeof(num3));  convertToLE(num3);
        file[2].read((char*)&nr, sizeof(nr));  convertToLE(nr);
        file[2].read((char*)&nc, sizeof(nc));  convertToLE(nc);
        if (magic != 2051 || num3 != 10000 || nr != 28 || nc != 28) {
            std::cout << "MNIST data files " << m_file_name[2] << " are corrupted." << endl;
            return false;
        }

        file[3].read((char*)&magic, sizeof(magic));  convertToLE(magic);
        file[3].read((char*)&num4, sizeof(num4));  convertToLE(num4);
        if (magic != 2049 || num4 != 10000) {
            std::cout << "MNIST data files " << m_file_name[3] << " are corrupted." << endl;
            return false;
        }

        return true;
    };
    void ProcessFiles(READ_FILE_METHOD METHOD = ALL) {
        // <ProcessFiles>
        // Toma un trozo (CHUNK) o tooos los datos (ALL) desde los archivos y los vuelca en memoria.
        // Para el ejemplo del MNIST no sirve de mucho ya que todos los datos para entrenar y para testear entran
        // perfectamente en memoria, pero pensando en un futuro con un dataset mas grande y pesado se tendra que subir
        // a memoria de a trozos para procesarlo en la red (supongo. ja!)

        if (IsFileFormatValid()) {
            ptr_train_image = new uint8_t[m_number_of_train_images * m_size_of_image];
            ptr_train_image_labels = new uint8_t[m_number_of_train_images];
            ptr_test_image = new uint8_t[m_number_of_test_images * m_size_of_image];
            ptr_test_image_labels = new uint8_t[m_number_of_test_images];

            switch (METHOD) {
            case ALL:
                // Vuelco en memoria, toda la info necesaria para el entrenamiento y testeo.
                file[0].read((char*)ptr_train_image, m_number_of_train_images * m_size_of_image);
                file[1].read((char*)ptr_train_image_labels, m_number_of_train_images);
                file[2].read((char*)ptr_test_image, m_number_of_test_images * m_size_of_image);
                file[3].read((char*)ptr_test_image_labels, m_number_of_test_images);
                break;
            case CHUNK:
                break;
            }
        }
        else exit(-1);
    }

    friend class MLP;
};

string FileManager::m_folder_name = "./data";
string FileManager::m_file_name[] = { "train-images-idx3-ubyte" ,"train-labels-idx1-ubyte" ,"t10k-images-idx3-ubyte" ,"t10k-labels-idx1-ubyte" };


class MLP {
private:
    FileManager m_file_manager;

    static const uint32_t m_input_size = FileManager::m_image_row_size * FileManager::m_image_col_size;
    static const uint32_t m_output_size = 10;
    static const uint32_t m_neurons_in_layers = 80;
    const float m_learning_rate = 0.01;

    // Inicializacion de los pesos sinapticos de cada capa, se suele dividir a los valores de la dsitribucion normal, por la entrada
    // de cada neurona (FAN IN) esto se hace para evitar que en el entrenamiento los pesos sinapticos se vayan a 0 o muy grandes.
    at::Tensor w1 = torch::randn({ m_input_size, m_neurons_in_layers })       .div(sqrtf(m_input_size))       .set_requires_grad(true);
    at::Tensor w2 = torch::randn({ m_neurons_in_layers, m_neurons_in_layers }).div(sqrtf(m_neurons_in_layers)).set_requires_grad(true);
    at::Tensor w3 = torch::randn({ m_neurons_in_layers, m_neurons_in_layers }).div(sqrtf(m_neurons_in_layers)).set_requires_grad(true);
    at::Tensor w4 = torch::randn({ m_neurons_in_layers, m_output_size })      .div(sqrtf(m_neurons_in_layers)).set_requires_grad(true);
    // fijate que se puede sacar o agregar capas, siempre y cuando se respete las dimensiones del primer y ultimo valor en este caso w1 y w4
    // se puede ver que todos los pesos sinapticos al ser variables que se van a optimizar luego, necesitan tener un gradiente para cuando
    // se aplique Backpropagation, por eso se ponen en TRUE, mientras que las entradas (que tambien son tensores) no lo necesitan.
public:
    MLP() {
        m_file_manager.ProcessFiles();
    }

    void Train() {
        cout << "TRAIN" << endl;
        // En esta forma de entrenamiento solo se pasa una imagen antes de hacer backpropagation, esto es lento e ineficiente, por eso comviene
        // agarrar de a lotes (BATCH) y despues de pasar el conjunto, se aplica el aprendizaje, esto se llama Stochastic Gradient Descent (SGD)
        // cuando pase  la biblioteca, es parte de las opciones.
        for (int idx = 0; idx < FileManager::m_number_of_train_images; idx++) {

            // este es el comando que se usa para acceder a memoria y crear los tensores, yo procure que toodas las imagenes esten de manera
            // contigua en memoria, para poder entrenar de a lotes (BATCH)(lo tengo que agregar).
            // fijate que como es una entrqada no necesita gradiente, por otro lado los bloques de memoria que contienen los datos son tipo 
            // CHAR ya que representan escala de grises. para poder entrenar, necesito que esten en FLOATS como los W's, por eso tambien lo
            // escalo el tensor para que en la imagen el mayor brillo sea 1 y orcuridad total 0.
            at::Tensor INPUT = torch::from_blob(m_file_manager.ptr_train_image + idx * m_input_size,
                { 1, FileManager::m_image_row_size * FileManager::m_image_col_size },
                at::kByte).set_requires_grad(false).to(at::kFloat) / 255.0f;

            // Aca se crea el vector de salida, con los resultados esperados, asi arme el vector para que solo tenga el valor 1 en la posicion
            // del numero correcto.
            at::Tensor OUTPUT = torch::zeros({ m_output_size }).to(at::kFloat);
            OUTPUT[m_file_manager.ptr_train_image_labels[idx]] = 1.0f;

            // Asi de simple es el Foward() en la red, solo multiplicacion de matrices, incluido al final de cada multiplicacion la funcion de
            // activacion CLAMP, que viene a jugar el papel de RELU como activacion.
            auto PREDICTION = INPUT.mm(w1).clamp(0).mm(w2).clamp(0).mm(w3).clamp(0).mm(w4);

            // Calculo el error, se auto explica el codigo.
            auto LOSS_PER_IMAGE = (PREDICTION - OUTPUT).pow(2).sum();

            // una vez que hice el Foward() viene el Backward() que me actualiza los gradientes de los W's segun el el LOSS encontrado.
            LOSS_PER_IMAGE.backward();

            // Aca aplico el gradiente para actualizar los W's fijate que depende del parametro de Learning uqe lo pones vos, por las pruebas que pude hacer
            // si lo pones muy grande puede llegar a  diverger y si lo pones muy bajo, toma muchisimos intentos para llegar a un resultado optimo.
            w1.set_data(w1.data() - m_learning_rate * w1.grad().data());
            w2.set_data(w2.data() - m_learning_rate * w2.grad().data());
            w3.set_data(w3.data() - m_learning_rate * w3.grad().data());
            w4.set_data(w4.data() - m_learning_rate * w4.grad().data());

            w1.grad().data().zero_();
            w2.grad().data().zero_();
            w3.grad().data().zero_();
            w4.grad().data().zero_();

            //cout << "#IMAGEN:<" << idx << "> Error: " << LOSS_PER_IMAGE.item<float>() << endl;
        }
    }

    void Test() {
        uint32_t OK = 0, FAIL = 0;
        bool show = true;

        cout << "TEST" << endl;
        cout << m_file_manager.m_number_of_test_images << " Imagenes que voy a testear. " << endl;

        for (size_t idx = 0; idx < m_file_manager.m_number_of_test_images; idx++) {

            // Tomo todas las imagenes del lote de Testeo y las pruebo una x una, comparo su salida con la que deberi ser correcta y llevo la cuenta.
            at::Tensor INPUT = torch::from_blob(m_file_manager.ptr_test_image + idx * m_input_size, { 1, m_input_size }, at::kByte).set_requires_grad(false).to(at::kFloat) / 255.0f;

            // Aca como la red ya esta entrenada solo se usa el Foward() que en este caso como esta echa a mano es la multiplicaion de las matrices que
            // guarda el resultado en PREDICTION.
            auto PREDICTION = INPUT.mm(w1).clamp(0).mm(w2).clamp(0).mm(w3).clamp(0).mm(w4);// .view({ D_out });

            if (PREDICTION.argmax().item<int>() == (int)m_file_manager.ptr_test_image_labels[idx])
                OK++;
            else {
                FAIL++;           
                /*
                // esto lo deje para verificar cuando no clasifica bien, podes activarlo si queres.
                cv::Mat IMAGE = cv::Mat(28, 28, CV_8UC1, m_file_manager.ptr_test_image[idx]);
                IMAGE.convertTo(IMAGE, CV_32F);

                at::Tensor RESULT = torch::zeros({ m_input_size }).to(at::kFloat);
                RESULT[m_file_manager.ptr_test_image_labels[idx]] = 1.00f;

                if (show == true) {
                    cout << " IMAGEN< " << idx << " >" << endl;
                    cout << IMAGE << endl;
                    cout << RESULT << endl;
                    cout << PREDICTION << endl;

                    std::string str;
                    std::getline(std::cin, str);
                    if (str != "n") show = false;
                }
                */
            }
        }
        cout << " OK:<" << OK << ">FAIL:<" << FAIL << ">  %(" << (float(OK) / (float(OK) + float(FAIL))) * 100 << ")." << endl;
    }
};

int main() {
    MLP perceptron;

    while (true) {
        perceptron.Train();
        perceptron.Test();
        cin.get();
    }

    return 0;
};
