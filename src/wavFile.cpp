	#include "../header.h"
	#include "wavFile.h"

	#ifndef __WavFile
	#define __WavFile
	#endif

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

	WavFile::WavFile(char *fileName)
	{
	    isFileExist(fileName);
	}

	int WavFile::checkFilesForHiding(char *parentFile, char *childFile)
	{
		if(isFileExist(parentFile) == -1)
		{
			throw("WAV non trouvé");
			return -1;
		}

		if(isFileExist(childFile)== -1)
		{
			throw("txt non trouvé");
			return -1;
		}
		return 0;
	}

	int WavFile::hide (char *parentFile, char *childFile, char *output)
	{
		FILE *wfile, *tfile, *ofile;
		unsigned char header[54];
		char wavbuffer, txtbuffer;
		int i;

		if(checkFilesForHiding(parentFile, childFile) == -1)
		{
			throw ("error!, initialization failed...");
			return -1;
		}

		wfile = fopen(parentFile, "rb");
		tfile = fopen(childFile, "rb");
		ofile = fopen(output, "w+b");

		fread(header, 54, 1, wfile);
		fwrite(header, 54, 1, ofile);

		while( ! feof(tfile) )
		{
			txtbuffer = fgetc(tfile);
			for(i = 0; i<8; i++)
			{
				wavbuffer = fgetc(wfile);
				wavbuffer &= 0xFE;
				wavbuffer |= (char)((txtbuffer >> i) & 1);
				fputc(wavbuffer,ofile);

				wavFileSize--;
			}
		}

		if(wavFileSize != 0)
		{
			while(!feof(wfile)) {
				fputc(fgetc(wfile), ofile);
            }
		}

		fclose(wfile);
		fclose(tfile);
		fclose(ofile);

		return 0;
	}

	int WavFile::unhide(char *parentFile, char *txtfile)
	{

		FILE *bfile, *tfile;
		char ch, bmpBuffer[8];
		int i;
		bfile = fopen(parentFile,"rb");
		tfile = fopen(txtfile,"w+b");

		fseek(bfile, 54, SEEK_SET);
		ch = 0;

		while(!feof(bfile))
		{
			ch = 0;
			for (i=0; i<=7; i++) {
				bmpBuffer[i] = fgetc(bfile);
			}

			for (i=7; i>=0; i--) {
				ch += (bmpBuffer[i] & 1);
				if(i != 0)
					ch <<= 1;
			}

			if(ch == EOF || ch == '*') {
				break;
			} else {
				fputc(ch,tfile);
			}
		}

		fclose(bfile);
		fclose(tfile);
		return 0;
	}
