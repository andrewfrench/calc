#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    printf("Hello, world. I'm running!");
    // Open a display.
    Display *d = XOpenDisplay(0);
    if(d){
       // Create the window
       Window w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 200,
			       100, 0, CopyFromParent, CopyFromParent,
			       CopyFromParent, 0, 0);

        // Show the window
        XMapWindow(d, w);
        XFlush(d);

	printf("Everything worked ok");

        // Sleep long enough to see the window.
        sleep(10);
    } else {
	printf("Error Error");
    }
    return 0;
}
