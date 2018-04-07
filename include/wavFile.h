class WavFile{
    private:
	public:
//		unsigned long wavFileSize;

		WavFile(char *filename);
		int isFileExist(char *filename);
		int checkFiles(char *parentfile, char *childfile);
		int encode(char *parentfile, char *childfile, char *outputfile);
		int decode(char *parentfile, char *txtfile);
		string getFileExt(char *txtfile);
};
