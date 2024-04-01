# cppvis

C++ Data Visualization Platform

Work in progress!

# Plans

- Pretty printing C++ data types in different notations (e.g. JSON, EDN)
- Syntax highlighting for pretty printing
- Different renderers (Terminal+Kitty/Sixel, PDF, Qt)
- Plotting and sparklines
- Interactivity
- Graph visualization 
- Dataframes and SQL

# Example Code

Most features are still unimplemented.

```c++
// pr prints EDN by default

std::map<std::string, char> M;
M.insert_or_assign("Key1", 'a');
M.insert_or_assign("Key2", 'b');
cppvis::prn(M);
//=> { "Key1" \a, "Key2" \b }

// Matlab style plot (not implemented)

cppvis::plot(std::vector<double>{ 1.0, 2.0, 3.0 }, std::vector<double>{ 1.0, 2.0, 3.0 });

// Loading images (not implemented)

auto img = cppvis::slurp("https://picsum.photos/500");
vis.prn(img);

```
