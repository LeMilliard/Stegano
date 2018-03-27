	#include "../header.h"
	#include "wavFile.h"

	#ifndef __WavFile
	#define __WavFile
	#endif

	WavFile::WavFile(char *fileName)
	{
	    isFileExist(fileName);
	}

	int WavFile::isFileExist(char *fileName)
	{
		FILE *wavFileName;
		wavFileName = fopen(fileName,"rb");
		if (wavFileName == NULL) {
			throw("Fichier non trouvé...\n");
			exit(1);
			return (-1);
		}
		fclose(wavFileName);
		return 0;
	}

	int WavFile::checkFiles(char *parentFile, char *childFile)
	{
		if(isFileExist(parentFile) == -1)
		{
			throw("WAV non trouve");
			return -1;
		}

		if(isFileExist(childFile)== -1)
		{
			throw("txt non trouve");
			return -1;
		}

		return 0;
	}

	int WavFile::encode (char *parent, char *child, char *output)
	{
		FILE *wFile, *tFile, *oFile;
		char wavBuffer, txtBuffer, lastBitChar;
		unsigned char header[54];
		int i;

		if(checkFiles(parent, child) == -1)
		{
			throw ("error!, verification fichiers...");
			return -1;
		}

		wFile = fopen(parent, "rb");
		tFile = fopen(child, "rb");
		oFile = fopen(output, "w+b");

		fread(header, 54, 1, wFile);
		fwrite(header, 54, 1, oFile);

		while( ! feof(tFile) )
		{
			txtBuffer = fgetc(tFile);
			//Pour chaque bit de l'octet
			for(i = 0; i<8; i++)
			{
			    // txtBuffer >> i permet de decaler vers la droite de i les bits
				// exemple 11110000 >> 1 = 01111000
				// le & 1 permet de recuperer le dernier bit du txtBuffer pour le merge avec le wavBuffer grâce au |
				// Attention ! On lis de droite à gauche donc il faudra remettre dans le bon ordre à la récupération
				lastBitChar = (txtBuffer >> i) & 1;

				wavBuffer = fgetc(wFile);

				// & avec OxFE permet de mettre de dernier bit à 0
				wavBuffer = wavBuffer & 0xFE;

				// merge le ieme bit du texte avec le wavBuffer grâce au |
				wavBuffer = wavBuffer | lastBitChar;
				fputc(wavBuffer,oFile);

				wavFileSize--;
			}
		}

		if(wavFileSize != 0)
		{
			while(!feof(wFile)) {
				fputc(fgetc(wFile), oFile);
            }
		}

		fclose(wFile);
		fclose(tFile);
		fclose(oFile);

		return 0;
	}

	int WavFile::decode(char *parent, char *txt)
	{

		FILE *bFile, *tFile;
		char c, buffer[8];
		int i;
		bFile = fopen(parent,"rb");
		tFile = fopen(txt,"w+b");

		// On skip le header
		fseek(bFile, 54, SEEK_SET);
		c = 0;

		while(!feof(bFile))
		{
			c = 0;
			for (i=0; i<=7; i++) {
				buffer[i] = fgetc(bFile);
			}

			// On lis à l'envers pour remettre les bits dans le bon ordre
			for (i=7; i>=0; i--) {
                    // & 1 permet de récupérer le bit de poid faible
				c += (buffer[i] & 1);
				if(i != 0)
					c <<= 1;
			}

			if(c == EOF) {
				break;
			} else {
				fputc(c,tFile);
			}
		}

		fclose(bFile);
		fclose(tFile);
		return 0;
	}
