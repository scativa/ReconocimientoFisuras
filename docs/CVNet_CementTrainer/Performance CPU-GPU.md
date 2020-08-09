# Performance
Comparación entre la performance utilizando Google Colab (GPU y CPU) y Linux Mint (CPU)

### Colab GPU

```
!time ./CVNet_CementTrainer2 --input=/content/5y9wdsg2zt-1 --epoch=10
real	0m5.083s
user	0m3.717s
sys	    0m1.441s
```

```
!time ./CVNet_CementTrainer2 --input=/content/5y9wdsg2zt-1 --epoch=100
real	0m13.154s
user	0m11.866s
sys	    0m2.264s
```
### Colab CPU

```
!time ./CVNet_CementTrainer2 --input=/content/5y9wdsg2zt-1 --epoch=10
real	0m26.989s
user	0m45.902s
sys	    0m0.774s
```
```
!time ./CVNet_CementTrainer2 --input=/content/5y9wdsg2zt-1 --epoch=100
real	4m30.172s
user	7m40.251s
sys	    0m6.787s
```
  
    
### Linux Mint CPU

```
time ./CVNet_CementTrainer2 --input=/home/seba/Proyectos/data/CementCrack/5y9wdsg2zt-1 --epoch=10
real	0m24,547s
user	0m56,327s
sys	    0m2,492s
```
```
time ./CVNet_CementTrainer2 --input=/home/seba/Proyectos/data/CementCrack/5y9wdsg2zt-1 --epoch=100
real	3m48,251s
user	9m14,874s
sys	    0m18,597s
```



