<H1>How to run the Basic Parallel Implementation</H1>
<H2>Type make in the BasicParallelImplementation directory</H2>
- Ensure that the input file and microtime.c are in the Root project folder (Not in the BasicParallelImplementation directory)
<H2>After typing make enter the command:</H2>

```
./mpirun -np {number of nodes} ./passguessmpiomp
```