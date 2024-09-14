#include "cortex.hh"

ark::ark(const char *filename){
    //loads the rgba values of the image//
    img = stbi_load(filename, &width,&height,&channels,4);
    if(img == NULL){
        log("Failed to load the image.")
    }
    log("Image loaded successfully")
}

ark::~ark(){
    stbi_image_free(img);
}
