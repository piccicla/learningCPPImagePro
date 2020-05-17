/*
 * read and copy bmp image
 * header format   http://www.fastgraph.com/help/bmp_header_format.html
 * */
 
#include <stdio.h>  //for c version
#include <stdlib.h>
//#include <iostream>  //for c++ version


#define BMP_HEADER_SIZE         54
#define BMP_COLOR_TABLE_SIZE    1024
#define CUSTOM_IMG_SIZE         1024*1024  //todo should be set with the input image

/*
int main(int argc, char **argv)
{
    //std::cout<< "sizeof(int)" << sizeof(int) << std::endl;
    //std::cout<< "sizeof(unsigned char)" << sizeof(unsigned char) << std::endl;
    printf("sizeof(int) %d\n", sizeof(int));
    printf("sizeof(unsigned char) %d\n", sizeof(unsigned char));

    FILE *streamin = fopen("images/cameraman.bmp","rb");
    FILE *streamout = fopen("images/cameraman_copy.bmp","wb");
      

    if(streamin==(FILE*)0){
        //std::cout<<"Could not open the file"<<std::endl;
        printf("Could not open the file\n");
        return 1;
    }
    
    unsigned char header[54];  // todo: how to make sure unsigned char is always 1 byte on all machines?
    unsigned char colorTable[1024];
    
    //reading the bmp 
    
    
    //std::cout<<"****Copying file to memory****"<<std::endl;
    printf("****Copying file to memory****\n");
    
    for(int i=0;i<54;i++){
            header[i]=getc(streamin);
    }
    
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];   // todo: how to make sure int is always 4 bytes on all machines?
    
    
    //std::cout<<"Width: "<<width <<std::endl;
    //std::cout<<"Height: "<<height <<std::endl;
    //std::cout<<"BitDepth: "<<bitDepth <<std::endl;
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    printf("BitDepth: %d\n", bitDepth);
    
    
    
    if(bitDepth<=8){
       fread(colorTable,sizeof(unsigned char),1024,streamin); 
    }
    unsigned char buf[height*width];
    fread(buf,sizeof(unsigned char),(height*width),streamin);

    //writing bmp
    
    //std::cout<<"****Saving file to disk****"<<std::endl;
    printf("****Saving file to disk****\n");
    
    fwrite(header,sizeof(unsigned char),54,streamout);
    if(bitDepth<=8){
       fwrite(colorTable,sizeof(unsigned char),1024,streamout); 
    }
    fwrite(buf,sizeof(unsigned char),(height*width),streamout);
    
    //
    fclose(streamin);
    fclose(streamout);
    
    //std::cout<<"****Done!****"<<std::endl;
    printf("****Done!****");
    
	return 0;
}*/


void  imageReader(const char *imgName,
                  int *_height,
                  int *_width,
                  int *_bitDepth,
                  unsigned char *_header,
                  unsigned char *_colorTable,
                  unsigned char *_buf
                  );
 void imageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char *buf,
                 int bitDepth) ;

int main()
{
    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgBuffer[CUSTOM_IMG_SIZE];  //todo: set when reading image

    const char imgName[] ="images/man.bmp";
    const char newImgName[] ="images/man_copy.bmp";
    
    //std::cout<<"****Copying file to memory****"<<std::endl;
    printf("****Copying file to memory****\n");
    imageReader(imgName, &imgWidth, &imgHeight, &imgBitDepth, &imgHeader[0], &imgColorTable[0], &imgBuffer[0]);
    
    //std::cout<<"****Saving file to disk****"<<std::endl;
    printf("****Saving file to disk****\n");
    imageWriter(newImgName, imgHeader, imgColorTable, imgBuffer, imgBitDepth);

    printf("Success !\n");

    return 0;
}


void  imageReader(const char *imgName,
                  int *_height,
                  int *_width,
                  int *_bitDepth,
                  unsigned char *_header,
                  unsigned char *_colorTable,
                  unsigned char *_buf
                  )
{
    int i;
    FILE *streamIn;
    streamIn = fopen(imgName, "rb");

    if(streamIn ==(FILE *)0)
    {

        printf("Unable to read image \n");
    }

    for(i =0;i<54;i++)
    {
        _header[i] = getc(streamIn);
    }

    *_width = *(int *)&_header[18];
    *_height = *(int *)&_header[22];
    *_bitDepth = *(int *)&_header[28];
    
    //std::cout<<"Width: "<<width <<std::endl;
    //std::cout<<"Height: "<<height <<std::endl;
    //std::cout<<"BitDepth: "<<bitDepth <<std::endl;
    printf("Width: %d\n", *_width);
    printf("Height: %d\n", *_height);
    printf("BitDepth: %d\n", *_bitDepth);


    if(*_bitDepth <=8)
    {
        fread(_colorTable, sizeof(unsigned char), 1024, streamIn);
    }

    fread(_buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, streamIn);

    fclose(streamIn);
}


void imageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char *buf,
                 int bitDepth)
   {
     FILE *fo = fopen(imgName, "wb");
     fwrite(header, sizeof(unsigned char), 54, fo);
     if(bitDepth <= 8)
     {
         fwrite(colorTable, sizeof(unsigned char), 1024, fo);
     }
     fwrite(buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, fo);
     fclose(fo);

   }