#include <iostream>
//Encabezado standar que define tipos de enteros con tamaños fijos, es decir
//uint8_t (8 bits sin signos), int16_t (16 bits con signo),uint32_t (32 bits
//sin signo), int64t (64 bits con signo).
#include <cstdint>
#include <fstream>
#include <vector>
using namespace std;

//Creamos una constante para evitar conflictos
constexpr int tamanoMemoria = 4096;

//Configuracion y estado de la CHIP-8.
struct maquina
{
	//Utilizo uint8_t en vez de unsigne char por temas de compatibilidad
	//ya que en otros sistemas puede tener problemas, es lo mismo pero
	//funciona en cualquier arquitectura.
	
	//Espacio para almacenar el codigo del juego y las variables
	//(son 4KB).
	uint8_t  memoria[tamanoMemoria];
	//Pantalla de 32 filas por 64 columnas
	uint8_t display[32][64] = {0};
	//Registro para los numeros hexadecimal
	uint8_t v[16];
	//Registro para almacenar direcciones de memoria
	uint16_t i;
};

class leerRoom
{
	public:
	void leerArchivo()
	{
    	//Utilizamos la siguiente linea seleccionar la ruta de un archivo
		//a una variable y a su vez lo abrimos pero en binario.
		ifstream leerArchivo("room.txt",ios::binary);

		//Obtenemos el tamaño exacto del contenido.
		leerArchivo.seekg(0,ios::end);
		size_t tamanoDelArchivo = leerArchivo.tellg();
		leerArchivo.seekg(0,ios::beg);

		//Hacemos comprobacion para saber si se abrio correctamente.
		if (leerArchivo.is_open())
		{
			//Leemos el contenido en un vector
			vector<uint8_t> contenido (tamanoDelArchivo);
			leerArchivo.read(reinterpret_cast<char *> (contenido.data()), tamanoDelArchivo);

			//Mostramos los primeros 16 bytes en hexadecimal
			cout << "El contenido en hexadecimal:\n";
			for (size_t i = 0; i< min (tamanoDelArchivo, size_t(16)); i++)
			{
				printf("%02X", contenido[i]);
			}
			cout << endl;
			leerArchivo.close();
		}
		else
		{
			cout <<"Error al leer archivo.";
		}
	}
};
int main ()
{
	cout << "Nada w\n";
    leerRoom c;
	c.leerArchivo();
	return 0;
}
