# DataBuilder - Error memalloc
Detalla el error de memoria al intentar crear el primer tensor de imágenes de 226x226 "5y9wdsg2zt-1\Negative"

## Salida
```
Informacion detallada mientras se ejecuta. <ON>
Direccion donde busca Imagenes. <C:\Users\User\Proyectos\data\CementCrack\5y9wdsg2zt-1>
Las Imagenes del tensor tienen dimension <226,226>

Procesando Directorios.
C:\Users\User\Proyectos\data\CementCrack\5y9wdsg2zt-1\Negative
```

## Código
__Dataset.cpp__
```cpp
Dataset::Pair Dataset::proccesing_data(
            IMG.push_back(get_image_from_directory(STR, "jpg",SIZE));


auto Dataset::get_image_from_directory(
    return torch::stack(torch::TensorList(IMG), 0);
```

__libtorch__
```cpp
    if (C10_LIKELY(unboxed_kernel_func_ != nullptr)) {
        using ActualSignature = Return (OperatorKernel*, Args...);
        ActualSignature* func = reinterpret_cast<ActualSignature*>(unboxed_kernel_func_);
        return (*func)(getFunctor_(), std::forward<Args>(args)...); <- Unhandled exception at 0x00007FF963C33E49 in CVNet_DatasetBuilder.exe: Microsoft C++ exception: c10::Error at memory location 0x000000B695CFCD00.
    }
```

## Call Stack

```
 	torch_cpu.dll!00007ff91753806f()	Unknown
 	torch_cpu.dll!00007ff9174c651f()	Unknown
 	torch_cpu.dll!00007ff917537d8c()	Unknown
 	torch_cpu.dll!00007ff9160d6f2f()	Unknown
>	CVNet_Data setBuilder.exe!c10::KernelFunction::callUnboxed<at::Tensor,c10::ArrayRef<at::Tensor>,__int64>(const c10::OperatorHandle & opHandle, c10::ArrayRef<at::Tensor> <args_0>, __int64 <args_1>) Line 66	C++
 	[Inline Frame] CVNet_DatasetBuilder.exe!c10::Dispatcher::callUnboxedWithDispatchKey(const c10::OperatorHandle &) Line 221	C++
 	[Inline Frame] CVNet_DatasetBuilder.exe!c10::Dispatcher::callUnboxed(const c10::OperatorHandle &) Line 229	C++
 	[Inline Frame] CVNet_DatasetBuilder.exe!c10::OperatorHandle::callUnboxed(c10::ArrayRef<at::Tensor>) Line 192	C++
 	[Inline Frame] CVNet_DatasetBuilder.exe!at::stack(c10::ArrayRef<at::Tensor>) Line 7851	C++
 	CVNet_DatasetBuilder.exe!Dataset::get_image_from_directory(const std::string & PATH, const std::string & EXT, const unsigned int & SIZE) Line 49	C++
 	CVNet_DatasetBuilder.exe!Dataset::proccesing_data(const std::string & SIZE, const std::string &) Line 68	C++
 	CVNet_DatasetBuilder.exe!Dataset::Dataset(const std::string & IMAGE_SIZE, const std::string &) Line 82	C++
 	CVNet_DatasetBuilder.exe!main(int argc, const char * * argv) Line 18	C++
 	[External Code]	
```
