/*
 * copy bmp image
 * 
 * */

#include <iostream>


int main(int argc, char **argv)
{
    
    
    FILE *streamin = fopen("images/cameraman.bmp","rb");
    FILE *streamout = fopen("images/cameraman_copy.bmp","wb");
      

    if(streamin==(FILE*)0){
        std::cout<<"Could not open the file"<<std::endl;
        return 1;
    }
    
    unsigned char header[54];
    unsigned char colorTable[1024];
    
    //reading the bmp 
    
    
    std::cout<<"****Copying file to memory****"<<std::endl;
    
    for(int i=0;i<54;i++){
            header[i]=getc(streamin);
    }
    
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];   //why cast to int, is a 2 byte number
    
    
    std::cout<<"Width: "<<width <<std::endl;
    std::cout<<"Height: "<<height <<std::endl;
    std::cout<<"BitDepth: "<<bitDepth <<std::endl;
    
    
    if(bitDepth<=8){
       fread(colorTable,sizeof(unsigned char),1024,streamin); 
    }
    unsigned char buf[height*width];
    fread(buf,sizeof(unsigned char),(height*width),streamin);

    //writing bmp
    
    std::cout<<"****Saving file to memory****"<<std::endl;
    
    
    fwrite(header,sizeof(unsigned char),54,streamout);
    if(bitDepth<=8){
       fwrite(colorTable,sizeof(unsigned char),1024,streamout); 
    }
    fwrite(buf,sizeof(unsigned char),(height*width),streamout);
    
    //
    fclose(streamin);
    fclose(streamout);
    
    std::cout<<"****Done!****"<<std::endl;
    
    

	return 0;
}
