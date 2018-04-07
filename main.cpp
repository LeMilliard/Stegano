
	#include "header.h"
    #include "wavFile.h"

	// function prototype
	int wavEncoderHandler(char *,char *, char *);
	int wavDecoderHandler(char *, char *);

	int main(int argc,char *argv[]) {
//wavEncoderHandler("ding.wav","download.jpg","testImage.wav");
//wavDecoderHandler("testImage.wav","decodeImage.jpg");
////
//wavEncoderHandler("ding.wav","song.txt","testTexte.wav");
//wavDecoderHandler("testTexte.wav","decodeTexte.txt");
		try {
			const char *f1 = argv[1];

			switch(argc)
			{
				case 1:
				case 2:
                case 3:
					exit(0);
					break;
				case 4:
					if ( strcmp(f1, "-d") == 0 ) {
						wavDecoderHandler(argv[2],argv[3]);
					} else {
						cout<<"example: "<<endl;
						cout<<"notre.exe -d embarqueLeCode.wav output.txt"<<endl;
						exit(0);
					}
					break;
				case 5:
					if ( strcmp(f1, "-e") == 0 ) {
						wavEncoderHandler(argv[2],argv[3],argv[4]);
					} else {
						cout<<"example: "<<endl;
						cout<<"notre.exe -e wavSansLeCode.wav texteAEncoder.txt embarqueLeCode.wav"<<endl;
						exit(0);
					}
					break;
			}
		}
		catch(char *err)
		{
			cout<<"Error : "<<err<<endl;
			exit(1);
		}

		return 0;
	}

	int wavEncoderHandler(char *parent, char *child, char *output)
	{
		WavFile wa(parent);
		if(wa.encode(parent, child, output) == -1)
			return -1;

		cout<<"encodage terminé"<<endl;
		return 0;
	};

	int wavDecoderHandler(char *parent, char *output)
	{
		WavFile wa(parent);
		if(wa.decode(parent,output)==-1)
			return -1;
		cout<<"decodage terminé"<<endl;
		return 0;
	};
