
ROOT_DIR=./
BUILD_DIR=./build
BIN_DIR=./bin

mkdir -p $BUILD_DIR
mkdir -p $BIN_DIR

# Set output file

# Changes directory to your execution directory (Leave as is)

cd $ROOT_DIR

# make the directories just in case


# Perform out of source build using build folder
cd $BUILD_DIR
cmake $ROOT_DIR
make
mv GeneticVision $BIN_DIR
rm -rf $BUILD_DIR
echo "Finished at $(date)"

