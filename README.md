<h1 align="center" style="color:white; background-color:black">Serverd</h1>
<h4 align="center">A server based on the frameworkd</h4>

<p align="center">
	<a href="http://zenith.eesc.usp.br/">
    <img src="https://img.shields.io/badge/Zenith-Embarcados-black?style=for-the-badge"/>
    </a>
    <a href="https://eesc.usp.br/">
    <img src="https://img.shields.io/badge/Linked%20to-EESC--USP-black?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/serverd/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/zenitheesc/serverd?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/serverd/issues">
    <img src="https://img.shields.io/github/issues/zenitheesc/serverd?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/serverd/commits/main">
    <img src="https://img.shields.io/github/commit-activity/m/zenitheesc/serverd?style=for-the-badge">
    </a>
    <a href="https://github.com/zenitheesc/serverd/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/zenitheesc/serverd?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/serverd/commits/main">
    <img src="https://img.shields.io/github/last-commit/zenitheesc/serverd?style=for-the-badge"/>
    </a>
    <a href="https://github.com/zenitheesc/serverd/issues">
    <img src="https://img.shields.io/github/issues-raw/zenitheesc/serverd?style=for-the-badge" />
    </a>
    <a href="https://github.com/zenitheesc/serverd/pulls">
    <img src = "https://img.shields.io/github/issues-pr-raw/zenitheesc/serverd?style=for-the-badge">
    </a>
</p>

<p align="center">
    <a href="#how-to-run">How to run?</a> •
    <a href="#dependencies">Dependencies?</a> •
    <a href="#how-to-build">How to build?</a> •
    <a href="#how-to-contribute">How to contribute?</a> •
</p>

<p align="center">
        <a href="README.pt.md">Versão em Portguês</a>
</p>

## How to run

You can either download the binary on the [Releases section](https://github.com/zenitheesc/serverd/releases), or you can build the project following the steps bellow.

## Dependencies

- [cmake](https://cmake.org/)
- [nlohmann's json library](https://github.com/nlohmann/json)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)

## How to build

First you need to install the necessary dependencies. On Debian based systems, you can install with the following command:

```bash
sudo apt install cmake nlohmann-json3-dev
```

For the cpp-httplib you have to clone the repo and follow the instructions on the [CMakeLists.txt](https://github.com/yhirose/cpp-httplib/blob/master/CMakeLists.txt).

After completing the dependencies, you can build the server with these steps:

```bash
mkdir build && cd build
cmake ..
make
```

To run the server just run:

```bash
./bin/Debug/Serverd
```

To test it you can use curl or any http client.

The server receives JSON's in OBSAT's format, like the example below:

```json
{
	"equipe": 41,
	"bateria": 24,
	"temperatura": 30,
	"pressao": 1,
	"giroscopio": [42,90,30],
	"acelerometro": [10,3,4],
	"payload": {
		"valor1": 3.1415,
		"classe":{
			"array1":[12,123,543],
			"valor2": "string"
		}
	}
}
```

A simple test can be made following these two steps.

Install curl.

```bash
sudo apt install curl
```
Send a JSON via curl.

```bash
curl --data @"<path-to-json>" localhost:8080
```

The server can accept two argument, the first one is the ip, the default is localhost
and the second is the port, the deafult is 8080. You can use the arguments as stated below:

```bash
./bin/Debug/Serverd <ip> <port>
```

## How to contribute

We love when new people come and help us to improve our software! If you want to contribute to this project, check our Projects board and pick an idea to develop. When you finish coding, make a clear and descriptive pull request explaining your modifications.

If you find any sort of problem or have a suggestion to the project, please write an issue and we will be pleased to help you!

---

<p align="center">
    <a href="http://zenith.eesc.usp.br">
    <img src="https://img.shields.io/badge/Check%20out-Zenith's Oficial Website-black?style=for-the-badge" />
    </a>
    <a href="https://www.facebook.com/zenitheesc">
    <img src="https://img.shields.io/badge/Like%20us%20on-facebook-blue?style=for-the-badge"/>
    </a>
    <a href="https://www.instagram.com/zenith_eesc/">
    <img src="https://img.shields.io/badge/Follow%20us%20on-Instagram-red?style=for-the-badge"/>
    </a>

</p>
<p align = "center">
<a href="zenith.eesc@gmail.com">zenith.eesc@gmail.com</a>
</p>
