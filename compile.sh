
mkdir -p build
mkdir -p bin

# Set output file

# Changes directory to your execution directory (Leave as is)



# Perform out of source build using build folder
cd build
cmake ..
make
cd ..
mv build/GeneticVision bin
rm -rf build
echo "Finished at $(date)"

