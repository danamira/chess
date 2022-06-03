<h1>SFML Smart Chess Application</h1>
<h2>About</h2>
<p>This is the second phase of my advanced programming class of the second semester of 2021-2022 academic year. A 'smart chess' application was needed to be written with the following functionalities:</p>
<ul>
<li>The ability to play chess on the with the ordinary logics of chess.</li>
<li>The app must be able to report 'dangerous` moves to the player. These are the moves which allow the opponent to win the game in the next one/two moves.</li>
<li>The app also must be able to report the best attacks. These are the moves which enable the player to mate his opponent in the next one/two moves.</li>
<li>The app must be able to receive an chess board(in a certain text template) and provide all the above functionalities to the user.</li>
<li>A graphical user interface must be designed using the SFML library in order to let the user play the game in a graphical environment.</li> 
</ul>
<h2>Implementation</h2>
This program simulates a real chess game through a graphical interface built by SFML library. It also finds the movies which make players vulnerable to mate-in-one or mate-in-two positions using a backtracking algorithm. In order to keep the visuals interesting, I mostly used images instead of SFML components as they provide more flexibility in terms of UI design.<br>
Here is an screenshot from the application:</p>
<p align="center">
	<img src="https://raw.githubusercontent.com/danamira/chess/main/.github/Preview.PNG" alt="Screenshot from the app">
</p>
<p>In the above-demonstrated situation, white is possibly in a mate-in-one posiiton. However, the black has analyzed all the moves for the knight located in F8. The program suggests that out of the two possible moves for this piece, one of them enables the white to win the game in one move but one of them is not particularly dangerous. The dangerous move is marked with the alert icon.</p>
<h2>Runnning the application</h2>
<p>Simply clone this repository, switch directory to the root folder of the project and run <code>g++ src/Main.cpp && ./a</code>. Please note that you must have SFML installed in advance, it can be painlessly installed on most of the GNU/Linux distors by <code>sudo apt install sfml</code>.</p>