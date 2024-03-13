# VHS documentation
#
# Output:
#   Output <path>.gif               Create a GIF output at the given <path>
#   Output <path>.mp4               Create an MP4 output at the given <path>
#   Output <path>.webm              Create a WebM output at the given <path>
#
# Require:
#   Require <string>                Ensure a program is on the $PATH to proceed
#
# Settings:
#   Set FontSize <number>           Set the font size of the terminal
#   Set FontFamily <string>         Set the font family of the terminal
#   Set Height <number>             Set the height of the terminal
#   Set Width <number>              Set the width of the terminal
#   Set LetterSpacing <float>       Set the font letter spacing (tracking)
#   Set LineHeight <float>          Set the font line height
#   Set LoopOffset <float>%         Set the starting frame offset for the GIF loop
#   Set Theme <json|string>         Set the theme of the terminal
#   Set Padding <number>            Set the padding of the terminal
#   Set Framerate <number>          Set the framerate of the recording
#   Set PlaybackSpeed <float>       Set the playback speed of the recording
#   Set MarginFill <file|#000000>   Set the file or color the margin will be filled with.
#   Set Margin <number>             Set the size of the margin. Has no effect if MarginFill isn't set.
#   Set BorderRadius <number>       Set terminal border radius, in pixels.
#   Set WindowBar <string>          Set window bar type. (one of: Rings, RingsRight, Colorful, ColorfulRight)
#   Set WindowBarSize <number>      Set window bar size, in pixels. Default is 40.
#   Set TypingSpeed <time>          Set the typing speed of the terminal. Default is 50ms.
#
# Sleep:
#   Sleep <time>                    Sleep for a set amount of <time> in seconds
#
# Type:
#   Type[@<time>] "<characters>"    Type <characters> into the terminal with a
#                                   <time> delay between each character
#
# Keys:
#   Escape[@<time>] [number]        Press the Escape key
#   Backspace[@<time>] [number]     Press the Backspace key
#   Delete[@<time>] [number]        Press the Delete key
#   Insert[@<time>] [number]        Press the Insert key
#   Down[@<time>] [number]          Press the Down key
#   Enter[@<time>] [number]         Press the Enter key
#   Space[@<time>] [number]         Press the Space key
#   Tab[@<time>] [number]           Press the Tab key
#   Left[@<time>] [number]          Press the Left Arrow key
#   Right[@<time>] [number]         Press the Right Arrow key
#   Up[@<time>] [number]            Press the Up Arrow key
#   Down[@<time>] [number]          Press the Down Arrow key
#   PageUp[@<time>] [number]        Press the Page Up key
#   PageDown[@<time>] [number]      Press the Page Down key
#   Ctrl+<key>                      Press the Control key + <key> (e.g. Ctrl+C)
#
# Display:
#   Hide                            Hide the subsequent commands from the output
#   Show                            Show the subsequent commands in the output

Output signals.gif

Require htop

Set Shell "zsh"
Set Theme "Dracula"
Set WindowBar Colorful
Set Margin 20
Set FontFamily "FiraCode Nerd Font Mono"
Set MarginFill "#6B50FF"
Set BorderRadius 10
Set FontSize 16
Set Width 1200
Set Height 600

Type@20ms "To take a look at the full list of UNIX Signals: 'man 7 signal'"
Sleep 2000ms
Backspace@5ms 80

Type "man 7 signal"
Sleep 1000ms
Enter
Sleep 1000ms

Type@150ms "/Standard"
Enter
Sleep 1000ms
Down@200ms 35
Sleep 100ms
Type "q"
Enter

Hide
Type "clear"
Enter
Show

Type@20ms "The simplest way to send a signal to a process is using the kill command."
Sleep 1000ms
Backspace@10ms 80

Type "kill <signal> <pid>"
Sleep 1000ms
Backspace@10ms 80

Type@20ms "Alternatively we can use a tool like htop to send a signal to a process."
Sleep 1000ms
Backspace@10ms 80

Type "htop"
Sleep 800ms
Enter

Type k
Up@40ms 20
Type o
Down@80ms 25
Sleep 1000ms
Ctrl+c

Hide
Type "clear"
Enter
Show

Type@20ms "Let's spin up a server to send a signal to."
Sleep 2000ms
Backspace@5ms 80

Type "../server &"
Sleep 500ms
Enter
Sleep 1000ms
Enter

Type "Let's kill the ../server process with the help of htop."
Sleep 800ms
Backspace@10ms 80

Sleep 200ms

Type "htop"
Sleep 500ms
Enter
Sleep 500ms

Type@200ms "/./server"
Sleep 2000ms
Enter

Sleep 1000ms
Type k
Sleep 2000ms
Enter
Sleep 2000ms
Ctrl+c

Sleep 200ms

Hide
Type "clear"
Enter
Show

Type@20ms "And so we sent a SIGTERM to the ../server process we had just started. "
Sleep 2000ms
Backspace@10ms 80

Type@20ms "The end! ✌ "
Sleep 2000ms
Backspace@10ms 80
