#include <iostream>
//Encabezado standar que define tipos de enteros con tamaños fijos, es decir
//uint8_t (8 bits sin signos), int16_t (16 bits con signo),uint32_t (32 bits
//sin signo), int64t (64 bits con signo).
#include <cstdint>
#include <fstream>
#include <vector>
using namespace std;

//Posible error en tamanoMemoria y su tamaño de tipo
constexpr uint16_t tamanoMemoria = 4096;
constexpr uint8_t  pantallaHorizontal= 64;
constexpr uint8_t  pantallaVertical = 32;

uint16_t interpreteRepetidor = 0x200;

//Configuracion y estado de la CHIP-8.
struct maquina
{
	//Utilizo uint8_t en vez de unsigne char por temas de compatibilidad
	//ya que en otros sistemas puede tener problemas, es lo mismo pero
	//funciona en cualquier arquitectura.
	
	//Espacio para almacenar el codigo del juego y las variables
	//(son 4KB).
	uint16_t memoria[tamanoMemoria];
	uint8_t pantallaTamano[pantallaVertical][pantallaHorizontal] = {0};
};

struct opcode
{
	void ejecutar (maquina& chip)
	{
		while (true)
		{
			
		}
	}
};

class leerRoom
{
	public:
	//Llamamos al objeto maquina y &chip se utiliza la instancia creada
	//y que se pueda modificar directamente (que no sea una copia de la
	//variable)
	void leerArchivo(maquina &chip)
	{
    	//Utilizamos la siguiente linea seleccionar la ruta de un archivo
		//a una variable y a su vez lo abrimos pero en binario.
		ifstream leerArchivo("room.txt",ios::binary);
		//Hacemos comprobacion para saber si se abrio correctamente.
    	if (leerArchivo.is_open())
    	{
    	    //Obtenemos el tamaño exacto del contenido.
    		leerArchivo.seekg(0,ios::end);
    		size_t tamanoDelArchivo = leerArchivo.tellg();
    		leerArchivo.seekg(0,ios::beg);
    
    		//Verificamos que el tamaño del archivo no sobrepase el tamaño de
    		//memoria asignada (recordemos que la maquina usa 512kb)
    		//0x000 a 0x1FF estan reservadas 0-511 kb
    		if (tamanoDelArchivo > (tamanoMemoria - 0x200))
    		{
    			return;
    		}
    		//Lee el archivo despues de la memoria 0x200 (512kb)
    		//reinterpret_cast convierte el archivo de uint_8 a char para que
    		//sea compartible, chip.memoria manda la ubicacion donde se
    		//pueda guardar las instrucciones a ese punto en la memoria.
    		leerArchivo.read(reinterpret_cast<char *>(&chip.memoria[0x200]), tamanoDelArchivo);

			//Mostramos los primeros 16 bytes en hexadecimal
			cout << "El contenido en hexadecimal:\n";
			for (size_t i = 0; i< min (tamanoDelArchivo, size_t(16)); i++)
			{
				//Imprimimos el contenido de la memoria despues del 512
				//porque solo se utilizara lo que hay despues de eso
				//y cambiamos la variable contenido a chip.memoria
				//ya que lo mostraremos directamente de la variable
				//principal.
				printf("%02X", chip.memoria[0x200 + i]);
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
    //Creamos una instancia para poder leer directamente en la
    //memoria
    maquina chip;
    //Llamamos la clase para leer la room
    leerRoom c;
    //Se declara chip para poder utilizarlo en LeerArchivo
	c.leerArchivo(chip);
	return 0;
}
