# cppvis

[![GitHub License](https://img.shields.io/github/license/rekola/cppvis?logo=github&logoColor=lightgrey&color=yellow)](https://github.com/rekola/cppvis/blob/main/LICENSE)
[![CI](https://github.com/rekola/cppvis/workflows/Ubuntu-CI/badge.svg)]()
[![VS17-CI](https://github.com/rekola/cppvis/workflows/VS17-CI/badge.svg)]()
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)

## C++ Data Visualization Platform

Work in progress!

## Features

- Pretty printing of C++ data structures in terminal with True Color

## Plans

- Image rendering (inline and block)
- Different notations for pretty printing (e.g. JSON, EDN)
- Different renderers (Terminal+Kitty/Sixel, PDF, Qt)
- Plotting and sparklines
- Interactivity
- Graph visualization
- Dataframes and SQL

## Example Code

Most features are still unimplemented.

```c++
// pr prints EDN by default

std::map<std::string, char> M;
M.insert_or_assign("key1", 'a');
M.insert_or_assign("key2", 'b');
cppvis::prn(M);
//=> { "key1" \a, "key2" \b }

// Matlab style plot (not implemented)

cppvis::plot(std::vector<double>{ 1.0, 2.0, 3.0 }, std::vector<double>{ 1.0, 2.0, 3.0 });

// Loading images (not implemented)

auto img = cppvis::slurp("https://picsum.photos/500");
vis.prn(img);

```
