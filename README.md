# qt_chess

In my spare time, I have been working on developing this game. The primary objective is to utilize a set of ready-made solutions from third-party libraries and integrate them into a fully functional application, effectively simulating real-world tasks.
The game is available for Windows. For easy access, you can find the installer in the repository.

Features:
1. **QML**-based user interface (UI) for an intuitive user experience.
2. For the backend, I implemented a tiny wrapper around a third-party **JavaScript** library, responsible for validating legal movements of chess pieces.
3. Additionally, the game use the third-party game engine **Stockfish.exe**, which simulates the opponent's moves.
4. To ensure smooth communication and integration, all these modules are connected by an application written in **C++**. This application uses protobuf messages that settles data exchange between the wrapper around the **JavaScript library** and the **C++** backend. (To optimize the generation of **protobuf** messages, I developed a **Python** script that efficiently navigates the directory containing the **proto** files, automatically creating messages for both the **C++** application and the **JavaScript** library. This automation ensures a faster developing process.)
5. The communication between the **C++** application and the **Stockfish** chess engine executable uses **Universal Chess Interface (UCI)**.
