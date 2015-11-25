# create a unique id for the build
UUID=$(uuidgen)
BUILD_DIR=build-$UUID

# create the build and bin directories
mkdir -p $BUILD_DIR
mkdir -p bin

# Set output file

# Changes directory to your execution directory (Leave as is)


# Change to build directory
cd $BUILD_DIR

# hook up gcc correctly


# Perform out of source build using build folder
export CC=$(which gcc)
export CXX=$(which g++)

cmake ..
make

# Change back to source directory
cd ..

# Move the resulting binary to bin directory
echo "Moving GeneticVision to $(pwd)/bin"
mv $BUILD_DIR/GeneticVision bin

echo "Deleting temp build directory $BUILD_DIR"
rm -rf $BUILD_DIR
echo "Finished at $(date)"

