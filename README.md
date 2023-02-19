# Pgeon 🐦

[![Build](https://github.com/0x0L/pgeon/actions/workflows/build.yml/badge.svg)](https://github.com/0x0L/pgeon/actions/workflows/build.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/0x0L/pgeon/blob/main/LICENSE)

The fastest flight from [PostgreSQL](https://www.postgresql.org/) to [Apache Arrow](https://arrow.apache.org/).

`pgeon` provides a C++ library and (very) simple python bindings. Almost all
PostgreSQL native types are supported (see [below](#notes)).

This project is similar to [pg2arrow](https://github.com/heterodb/pg2arrow) and is heavily inspired by it. The main differences are the use of `COPY` instead of `FETCH` and that our implementation uses the Arrow C++ API.

## Usage

```python
from pgeon import copy_query
db = "postgresql://postgres@localhost:5432/postgres"
query = "SELECT TIMESTAMP '2001-01-01 14:00:00'"
tbl = copy_query(db, query)
```

The actual query performed is `COPY ({query}) TO STDOUT (FORMAT binary)`, see [this page](https://www.postgresql.org/docs/current/sql-copy.html) for more information.

## Install notes

`pgeon` requires [libpq](https://www.postgresql.org/docs/current/libpq.html) to be available on your system. You'll also need a C++ compiler.

### Python

The preferred way to get started is to use conda. This will take care of all the dependencies.

```shell
conda env create -f environment.yml
conda activate pgeon-dev
pip install .
```

See [this issue](https://github.com/0x0L/pgeon/issues/8) for installation in a non conda based environment.

### [optional] C++ library and tools

This requires [cmake](https://cmake.org/) and [ninja](https://ninja-build.org/)

```shell
mkdir build
cd build
cmake -GNinja ..
ninja
```

## Performance

Elapsed time distributions of a query fetching 7 columns (1 timestamp, 2 ints, 4 reals) and around 4.5 million rows. The result is returned as a `pandas.DataFrame` in all cases.

![](benchmarks/minute_bars.svg)

## Notes

- Queries using `ROW` (e.g. `SELECT ROW('a', 1)`) do not work

- SQL arrays are mapped to `pyarrow.list_(...)`. Only 1D arrays are fully supported. Higher dimensional arrays will be flattened.

- BitString types output format is not really helpful

- tsvector types with letter weights are not supported

- PostgreSQL range and domain types are not supported.

