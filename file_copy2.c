#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	
	int fdin,fdout,size;
	ssize_t nread;
	char* buffer;
	
	//option
	if(argc!=3){
		printf("copy [sourcefile] [dest file]");
		exit(-1);
	}
	
	// file open
	fdin=open(argv[1],O_RDONLY);
	fdout=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0644);
	
	// file open error	
	if(fdin<0 ||fdout<0){
		printf("file open error\n");
	}
	
	// seek
	size=(int)lseek(fdin,(off_t)0,SEEK_END); // 12
	lseek(fdin,(off_t)0,SEEK_SET); // pointer move first byte
	buffer=(char*)malloc(size);
	
	// file read
	nread=read(fdin,buffer,size);

	// file read error
	if(nread==0){
		printf("read no data\n");
		exit(-1);
	}
	else if(nread<0){
		printf("read error\n");
		exit(-1);
	}
	if(nread>0){
		printf("read success\n");
		if(write(fdout,buffer,nread)==nread){
			printf("write success\n");
		}
		else if(write(fdout,buffer,nread)<nread){
			printf("copy error\r\n");
			close(fdin);
			close(fdout);
		}
	}
	
	free(buffer);

	close(fdin);
	close(fdout);

	return 0;

}
