#include <apps/endbar.h>
#include <endfs.h>
#include <hooking.h>
#include <keyboard.h>
#include <mouse.h>
#include <ncurses.h>
#include <unistd.h>
#include <window.h>
#include <yhookmin.h>

typedef struct {
	int menu_toggle_key;
} settings_t;

settings_t settings;
EWH* settingsWindow = NULL;

yHook_t pkh;

void process_keypress_H(int key, endui_mouse* mouse, vec_void_t* handles, EWH** drag_window) {
	if (key == settings.menu_toggle_key) {
		main_menu->hidden = !main_menu->hidden;
	} else {
		yHookTrampoline(pkh, process_keypress, key, mouse, handles, drag_window);
	}
}

char* settings_to_bin(settings_t* settings) {
	char* bin = malloc(sizeof(*settings));

	memcpy(bin, settings, sizeof(*settings));

	return bin;
}

void bin_to_settings(settings_t* settings, char* bin) {
	memcpy(settings, bin, sizeof(*settings));
}

void save_cfg(settings_t* settings) {
	char* bin = settings_to_bin(settings); /* write default config */
	write_file("./endui.bin", bin);
	free(bin);
}

void load_cfg(settings_t* settings) {
	char* bin = read_file("./endui.bin");
	bin_to_settings(settings, bin);
	free(bin);
}

bool setMenuBindCallback(struct EWH* sender, void* arg) {
	nodelay(stdscr, FALSE);
	mvwprintw(stdscr, 0, 0, "Press any key...");
	wrefresh(stdscr);
	settings.menu_toggle_key = wgetch(stdscr);
	nodelay(stdscr, TRUE);

	snprintf(sender->title, WINDOW_TITLE_MAX, "Menu: %c", (char)settings.menu_toggle_key);

	save_cfg(&settings);
	return true;
}

int settings_main(void) {
	EWH *labelKeybinds, *separatorKeybinds, *bindMenuButton, *infoLabel;

	settings.menu_toggle_key = 'h';

	if (access("./endui.bin", F_OK) == -1) {
		save_cfg(&settings);
	} else {
		load_cfg(&settings);
	}

	settingsWindow = ewh_new_window(17, 1, 20, 10, "Settings");
	labelKeybinds = ewh_new_label(1, 2, "Keybinds: ", settingsWindow);
	separatorKeybinds = ewh_new_separator(1, 5, 18, settingsWindow);
	bindMenuButton = ewh_new_button(1, 3, 9, 1, "Menu: ", settingsWindow);
	snprintf(bindMenuButton->title, WINDOW_TITLE_MAX, "Menu: %c", (char)settings.menu_toggle_key);
	bindMenuButton->ewh_callback = setMenuBindCallback;

	separatorKeybinds->width = separatorKeybinds->parent->width - 2;

	infoLabel = ewh_new_label(1, 7, "EndUI by aceinetx", settingsWindow);

	pkh = yHookInstall((yaddr_t)process_keypress, (yaddr_t)process_keypress_H);
	yHookEnable(pkh);

	settingsWindow->hidden = true;
	ewh_add(settingsWindow);
	ewh_add(labelKeybinds);
	ewh_add(separatorKeybinds);
	ewh_add(bindMenuButton);
	ewh_add(infoLabel);
	return 0;
}
