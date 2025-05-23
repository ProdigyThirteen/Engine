
## Getting Started

### Prerequisites

- **CMake 3.26+**
- **C++23** compatible compiler:
  - **Windows**: Visual Studio 2022 (v17.5+) or MSYS2/MinGW-w64
  - **Linux**: GCC 13+ or Clang 16+

###  Building the Project

<details>
<summary> Windows </summary>

```powershell
git clone https://github.com/ProdigyThirteen/Engine.git
cd Engine
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug
```
</details>

<details>
<summary> Linux</summary>
  
```bash
git clone https://github.com/yourusername/your-repo.git
cd your-repo
mkdir build
cd build
cmake -DCMAKE_CXX_STANDARD=23 ..
cmake --build .
```
</details>


## Running the Hello World Example


<details>
<summary> Windows </summary>
  
```powershell
cd build\Examples\HelloWorld\Debug
HelloWorld.exe
```
</details>

<details>
<summary> Linux</summary>
  
```bash
cd build/Examples/HelloWorld
./HelloWorld
```
</details>
