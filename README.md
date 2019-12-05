# Notify
[![Gitter](https://badges.gitter.im/notify_music/community.svg)](https://gitter.im/notify_music/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Find the notes of your favorite piano music using Notify.
Notify tries to figure out musical notes from any WAV file that contains piano music.

Notify obtains the audio spectrum using a Fast Fourier Transform library ([simpleFFT](https://github.com/d1vanov/Simple-FFT)). This spectrum is analyzed and contributions of each piano key are calculated to identify key presses using least square solutions of linear equations.

## Installation

Currently supported only on Windows.
(Cross platform support coming soon!)

 1. Download and install [Microsoft Visual Studio IDE](https://visualstudio.microsoft.com/). Elaborate instructions can be found [here](https://tutorials.visualstudio.com/cpp-console/install). Make sure to install the "Dektop development with C++" pack during installation.
 2. Download and extract the Eigen library using this [link](http://bitbucket.org/eigen/eigen/get/3.3.7.zip) in the C: Drive (or anywhere you want, as long as you remember the path to the extracted directory).
 3. Clone this repository using the following command:
````
git clone https://github.com/ShreyanshDarshan/Notify.git
````
 4. Open Notify.vcxproj in Visual Studio IDE.
 5. In the solution explorer, right click on **Notify** and select **Properties**. Under **General** properties of **C/C++** section, edit the **Additional Include Directories** and change the path written for the directory of EIgen library to the one where it is in your system. Also change the path of the simple_fft library to the path in your system, i.e. path_of_Notify/simple_fft.

Done! Problems encountered during installation can be discussed on the communication channel.

## Usage

Currently, WAV files are given only by editing the code. The code can be run by building the solution (F7) and starting debugger (F5) or starting without debugger (ctrl+F5).
