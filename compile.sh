$UUID=$(uuidgen)
$BUILD_DIR=build/$UUID
mkdir -p $BUILD_DIR
mkdir -p bin

# Set output file

# Changes directory to your execution directory (Leave as is)



# Perform out of source build using build folder
cd $BUILD_DIR
cmake ../..
make
cd ../..
mv $BUILD_DIR/GeneticVision bin
rm -rf $BUILD_DIR
echo "Finished at $(date)"

