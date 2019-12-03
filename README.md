# Notify
----
[![Gitter](https://badges.gitter.im/notify_music/community.svg)](https://gitter.im/notify_music/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
----
Find the notes of your favorite piano music using Notify.
Notify tries to figure out musical notes from any WAV file that contains piano music.

Notify obtains the audio spectrum using a Fast Fourier Transform library ([simpleFFT](https://github.com/d1vanov/Simple-FFT)). This spectrum is analyzed and contributions of each piano key are calculated to identify key presses using least square solutions of linear equations.

## Installation

Currently supported only on Windows.
(Cross platform support coming soon!)

 1. Download and install [Microsoft Visual Studio IDE](https://visualstudio.microsoft.com/). Elaborate instructions can be found [here](https://tutorials.visualstudio.com/cpp-console/install).
 2. Clone this repository using the following command:
````
git clone https://github.com/ShreyanshDarshan/Notify.git
````
Done! Problems encountered during installation can be discussed on the communication channel.
