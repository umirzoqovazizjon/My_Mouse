# Welcome to My Mouse
***

## Task
This project is about finding the shortest path between entering and leaving a labyrinth while avoiding obstacles

## Description
![labyrinth](https://storage.googleapis.com/qwasar-public/s02_SE/my_mouse_maze.jpg)
* Definition of a valid map :
    * All lines must respect the sizes given in the first line (LINExCOL).
    * There can only be one entrance.
    * There must be at least one exit and only one.
    * There must be a solution to the labyrinth.
    * The labyrinth will not be more than a thousand square.
    * At the end of each line, there is a new line.
    * The characters present in the map must be only those shown on the first

## Installation
compile `my_mouse` project with `Makefile` by using this command
```shell
$> make
```
## Usage
* `filename` - Built-in files `labyrinth.map`, `01.map`, `02.map`, `03.map`. You can create your own custom map by rules, save it to a file and use it.
```shell
$> ./my_mouse ["filename"]
```
* Generation maps, usage and example:
  * [`height`] - Map height.
  * [`width`] - Map width.
  * `characters` - by default "`* o12`"
    ```shell
    $> ruby maze_generator.rb ["height"] ["width"] ["characters"]

    $> ruby maze_generator.rb 10 10 "* o12"
    $> ./my_mouse "test.map"
    ```
* Using ruby code to verify program correctness
    ```shell
    $> ./my_mouse "filename" | ruby my_mouse_checker.rb

    $> ./my_mouse "labyrinth.map" | ruby my_mouse_checker.rb
    ```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>