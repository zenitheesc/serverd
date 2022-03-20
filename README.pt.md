## Como rodar

Você pode tanto baixar o executável na parte de [Release](https://github.com/zenitheesc/serverd/releases), ou também é possível buildar
o projeto fazendo as etapas abaixo.

## Dependências

- [cmake](https://cmake.org/)
- [nlohmann's json library](https://github.com/nlohmann/json)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)

## Como compilar

Primeiro, é preciso instalar as dependências, no Ubuntu você pode instalar o cmake e a biblioteca json com o comando abaixo:

```bash
sudo apt install cmake nlohmann-json3-dev
```

Para o cpp-httplib você tem de clonar o repositório e seguir as instruções no [CMakeLists.txt](https://github.com/yhirose/cpp-httplib/blob/master/CMakeLists.txt) da biblioteca.

Após resolvidas as dependências, rode os comando abaixo para compilar o servidor:

```bash
mkdir build && cd build
cmake ..
make
```

Para rodá-lo use o comando abaixo:

```bash
./bin/Debug/Serverd
```

Para testar você pode usar o curl ou qualquer outro cliente http.

O servidor recebe JSON's no formato da OBSAT, igual o demonstrado a seguir:

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

Um simples test pode ser feito seguindo os seguintes passos:

Instale o curl.

```bash
sudo apt install curl
```

Envie o json via curl para o servidor.

```bash
curl --data @"<caminho-para-o-json>" localhost:8080
```

O servidor pode aceitar dois argumentos, o primeiro é o ip, o padrão é localhost
e o segundo é a porta, por padrão é a 8080, Você pode usar os argumentos como é demonstrado abaixo:

```bash
./bin/Debug/Serverd <ip> <porta>
```

## Como contribuir

Nós adoramos quando novas pessoas vem nos ajudar a melhorar o nosso software! Se você quer contribuir com esse projeto, de uma olhada na parte de Projects e escolha uma ideia para desenvolver. Quando terminado o desenvolvimento, faça um pull request claro e descritivo explicando as suas modificações.
Se você achar qualquer problema ou tem alguma sugestão para o projeto, por favor escreva uma issue e nós estremos disposto para ajudá-lo.

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
