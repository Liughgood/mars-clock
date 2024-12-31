# Mars Clock

Mars Clock 是一个用于计算火星时间的项目。该项目包括计算火星时间的核心功能和相应的单元测试。

## 项目结构

```
mars-clock/
├── include/
│   ├── clock.h
│   ├── main.h
│   └── test.h
├── src/
│   ├── clock.c
│   ├── main.c
│   └── test.c
├── obj/
├── bin/
├── Makefile
└── README.md
```

- `include/` 目录包含项目的头文件。
- `src/` 目录包含项目的源文件。
- `obj/` 目录用于存放编译生成的目标文件。
- `bin/` 目录用于存放编译生成的可执行文件。
- `Makefile` 文件用于项目的编译和构建。
- `README.md` 文件是项目的文档说明。

## 编译和运行

### 编译项目

要编译项目，请在项目根目录下运行以下命令：

```sh
make all
```

这将编译项目并生成两个可执行文件：`main` 和 `test`。

### 运行主程序

要运行主程序，请在项目根目录下运行以下命令：

```sh
make main
./bin/main
```

### 运行测试

要运行测试，请在项目根目录下运行以下命令：

```sh
make test
./bin/test
```

## 文件说明

### `main.c`

`main.c` 文件包含主函数 `main()`，用于调用 `calculate_mars_time()` 函数并输出当前火星时间。

### `clock.c`

`clock.c` 文件包含计算火星时间的核心功能，包括以下函数：

- `currentTimeMillis()`
- `getJDut()`
- `getJDtt()`
- `getDeltaTj2000()`
- `calculateM()`
- `calculateAlphaFMS()`
- `calculatePBS()`
- `calculateVM()`
- `calculateLs()`
- `calculateEOT()`
- `calculateMSD()`
- `calculateMST()`
- `calculateLMST()`
- `calculateLTST()`
- `calculate_mars_time()`

### `test.c`

`test.c` 文件包含单元测试，用于测试 `clock.c` 文件中的函数。测试使用 CUnit 框架编写。

### `Makefile`

`Makefile` 文件用于项目的编译和构建。包含以下目标：

- `all`：编译项目并生成 `main` 和 `test` 可执行文件。
- `main`：编译并生成 `main` 可执行文件。
- `test`：编译并生成 `test` 可执行文件。
- `clean`：删除生成的目标文件和可执行文件。

## 依赖

- [CUnit](http://cunit.sourceforge.net/)：一个用于 C 语言的单元测试框架。

## 贡献

欢迎贡献代码！请提交 Pull Request 或报告 Issue。

## 许可证

本项目采用 MIT 许可证。有关详细信息，请参阅 LICENSE 文件。

## 参考

- [算法和示例](https://liughgood.github.io/GenhaoLog/nasa/mars/time/2024/12/17/algorithm-and-worked-examples.html)
- [NASA Mars24](https://www.giss.nasa.gov/tools/mars24/)
- [Mars Clock](http://marsclock.com)
