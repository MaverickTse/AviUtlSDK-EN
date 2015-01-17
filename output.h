//----------------------------------------------------------------------------------
//	Header file for export plugin : AviUtl version 0.99g4 and after
//	By Ken, Translated by Maverick Tse
//----------------------------------------------------------------------------------

//	Output Info Struct
typedef struct {
	int		flag;			//	Flag
							//	OUTPUT_INFO_FLAG_VIDEO	: Has Video data
							//	OUTPUT_INFO_FLAG_AUDIO	: has Audio data
							//	OUTPUT_INFO_FLAG_BATCH	: Batch encoding...
	int		w,h;			//	resolution
	int		rate,scale;		//	framerate
	int		n;				//	frames selected for export
	int		size;			//	bytes per frame
	int		audio_rate;		//	audio sample rate
	int		audio_ch;		//	audio channel count
	int		audio_n;		//	audio sample count
	int		audio_size;		//	byte per audio sample
	LPSTR	savefile;		//	pointer to file name for saving
	
	//	Return pointer to image data (BGR24bit)
	//	frame	: frame no.
	//	Return	: pointer
	//			  Pointer content is valid until next external function is called or returned to MAIN
  //        Returned data use the idea of "Stride"(byte size per line) which equals oip->size/oip->h
  //        When oip->w is not a multiple of 8, Stride > (oip->w * 3)
	void	*(*func_get_video)( int frame );
	
	
	//	Get a pointer to 16bitPCM audio data
	//	start	: starting sample no.
	//	length	: no. of samples to be read
	//	readed	: no. of samples already read
	//	Return	: Pointer to data
	//			  Pointer content is valid until next external function is called or returned to MAIN
	void	*(*func_get_audio)( int start,int length,int *readed );


	//	Check if user aborted encoding
	//	Return	: TRUE if aborted	
	BOOL	(*func_is_abort)( void );

	
	//	Display remaining time
	//	now		: processing frame
	//	total	: total frames to be processed
	//	Return	: TRUE if successful
	BOOL	(*func_rest_time_disp)( int now,int total );

	
	//	Get status flag
	//	frame	: frame no.
	//	Return	: Flag
	//  OUTPUT_INFO_FRAME_FLAG_KEYFRAME		: Suggested keyframe
	//  OUTPUT_INFO_FRAME_FLAG_COPYFRAME	: Suggested copy-frame
	int		(*func_get_flag)( int frame );

	
	//	Update preview window
	//	The last frame read by func_get_video will be shown at the end
	//	Return	: TRUE if successful
	BOOL	(*func_update_preview)( void );


	//	Get image data as DIB format
	//	frame	: frame no.
	//	format	: Image format( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 / 'Y''C''4''8' = PIXEL_YC )
	//			  ※PIXEL_YC format is unavailable in YUY2 filter mode
	//	Return	: pointer to data
	//			  Pointer content is valid until next external function is called or returned to MAIN
  //        Returned data use the idea of "Stride"(byte size per line) which equals oip->size/oip->h
  //        When oip->w is not a multiple of 8, Stride > (oip->w * 3) 
	void	*(*func_get_video_ex)( int frame,DWORD format );

} OUTPUT_INFO;


#define	OUTPUT_INFO_FLAG_VIDEO	1
#define	OUTPUT_INFO_FLAG_AUDIO	2
#define	OUTPUT_INFO_FLAG_BATCH	4
#define	OUTPUT_INFO_FRAME_FLAG_KEYFRAME		1
#define	OUTPUT_INFO_FRAME_FLAG_COPYFRAME	2

//	Struct of Export plugin
typedef	struct {
	int		flag;			//	flag
	LPSTR	name;			//	plugin name
	LPSTR	filefilter;		//	file-type filter
	LPSTR	information;	//	plugin info
	BOOL	(*func_init)( void );
							//	pointer to function to be called when DLL starts. use NULL to skip.
	BOOL	(*func_exit)( void );
							//	pointer to function to be called when DLL ends. use NULL to skip.
	BOOL	(*func_output)( OUTPUT_INFO *oip );
							//	pointer to function that handle actual export.
	BOOL	(*func_config)( HWND hwnd,HINSTANCE dll_hinst );
							//	pointer to function when calling setting dialog. use NULL to skip.
	int		(*func_config_get)( void *data,int size );
							//	pointer to function for getting setting data. NULL to skip.
							//	data	: pointer to buffer for storing setting data .NULL to skip.
							//	size	: buffer size
							//	Return	: size of setting data
	int		(*func_config_set)( void *data,int size );
							//	pointer to function when saving settings. NULL to skip.
							//	data	: pointer to setting data
							//	size	: size of setting data
							//	Return	: Consumed data size
	int		reserve[16];	//	Reserved
} OUTPUT_PLUGIN_TABLE;

BOOL func_init( void );
BOOL func_exit( void );
BOOL func_output( OUTPUT_INFO *oip );
BOOL func_config( HWND hwnd,HINSTANCE hinst );
int func_config_get( void *data,int size );
int func_config_set( void *data,int size );


