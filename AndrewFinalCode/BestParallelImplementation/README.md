<H1>How to run the Best Parallel Implementation</H1>
<H2>Type make in the BestParallelImplementation directory</H2>
- Ensure that the input file and microtime.c are in the Root project folder (Not in the BestParallelImplementation directory)
<H2>After typing make enter the command:</H2>

```
./mpirun -np {number of nodes} ./passguessmpiomp
```