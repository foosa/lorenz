# lorenz
lorenz attractor implemented in C

![lorenz-attractor](lorenz.png)

## Usage:

	gcc lorenz.c -o lorenz -lm -lgsl
	./lorenz > data.csv
	gnuplot -e "set terminal png; splot 'data.csv' using 2:3:4 with lines" > lorenz.png

