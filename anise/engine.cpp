#include "engine.h"

Engine::Engine(Option *option)
{
	this->option = option;
}


Engine::~Engine()
{
}


bool Engine::on()
{
	//TODO: move this method into constructor?

	//TODO: initialize font

	//TODO: initialize video, mouse and keyboard (SDL related)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		PRINT("[Engine::initialize()] unable to initialize SDL backend: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_WM_SetCaption(TITLE, NULL);

#ifdef _WIN32
	SDL_SysWMinfo info;
	SDL_VERSION(&(info.version));
	SDL_GetWMInfo(&info);

	HINSTANCE hInstance = GetModuleHandle(NULL);
	HWND hWnd = info.window;

	int small_icon_width = GetSystemMetrics(SM_CXSMICON);
	int small_icon_height = GetSystemMetrics(SM_CYSMICON);

	int large_icon_width = GetSystemMetrics(SM_CXICON);
	int large_icon_height = GetSystemMetrics(SM_CYICON);

	HICON small_icon = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_ANISE), IMAGE_ICON, small_icon_width, small_icon_height, LR_DEFAULTCOLOR);
	HICON large_icon = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_ANISE), IMAGE_ICON, large_icon_width, large_icon_height, LR_DEFAULTCOLOR);

	SendMessage(hWnd, WM_SETICON, (WPARAM) ICON_SMALL, (LPARAM) small_icon);
	SendMessage(hWnd, WM_SETICON, (WPARAM) ICON_BIG, (LPARAM) large_icon);
#endif

	memory = new Memory(option);
	video = new Video(memory, option);
	sound = new Sound(option);
	timer = new Timer(video);
	input = new Input(memory, timer);

	script = new Script(memory, video, sound, timer, input, option);

	return true;
}


bool Engine::off()
{
	delete script;
	delete input;
	delete video;
	delete timer;
	delete memory;

	SDL_Quit();

	return true;
}


bool Engine::run()
{
	script->load(option->script_file_name);
	SCRIPTCALL condition = script->parse();
	
	PAUSE;

	return true;
}