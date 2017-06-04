#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  char estado[9]; // activo o inactivo
  char codigo[11];
  char nombre[22];
  char apellido[40];
  char celular[11];
  char edad[2];
  struct progra {
    char nombrePrograma[50];
    char codigoPrograma[5];
    int semestres;
    struct materia {
      char nombreMateria[50];
      char codigoMateria[7];
      char nombreProfesor[50];
      char periodoaca[5];
      float parcial1;
      float parcial2;
      float parcial3;
      float parcial4;
      float definitiva;
    }materias[4];
  }infoprog[4];
}Estudiante;

// Funcion que pausa la ejecucion del programa hasta que el usuario presiona Enter
void pausar() {
  printf("Presione ENTER para continuar\n");
  while (getchar() != '\n');
  getchar();
}

// Funcion para crear un objeto de estudiante
Estudiante crearEstudiante(char* nombreArchivo) {
  Estudiante estudiante; // Objeto para crear el estudiante
  // Abrir en modo "a" por si no existe el archivo, crearlo
  FILE* file = fopen(nombreArchivo, "ab");

  if (file == NULL) {
    printf("Error al abrir el archivo\n");
    return estudiante;
  }
  else {
    fclose(file); // Cerrarlo y abrir en modo solo lectura
    file = fopen(nombreArchivo, "rb");
    Estudiante comparacion;// Objeto para verificar que no exista el estudiante
    int existe = 0; // Bandera para saber si existe el estudiante

    printf("\n\tIngrese el codigo: "); fflush(stdin);
    scanf(" %[^\n]", estudiante.codigo);

    // Verificar que el estudiante no este registrado ya:
    while( fread(&comparacion, sizeof(Estudiante), 1, file)) {
      if( strcmp(estudiante.codigo, comparacion.codigo) == 0 ) {
        existe = 1; // Si encuentra alguien con el mismo codigo, pone esta variable en 1
                    // en caso contrario esta permanecera en 0 como fue definida
      }
    }
    fclose(file);

    // Si es usuario NO existe se crea.
    if (existe == 0) {
      strcpy(estudiante.estado, "activo");

      printf("\n\tIngrese el nombre: ");fflush(stdin);
      scanf(" %[^\n]", estudiante.nombre);

      printf("\n\tIngrese el apellido: ");fflush(stdin);
      scanf(" %[^\n]", estudiante.apellido);

      printf("\n\tIngrese el celular:");fflush(stdin);
      scanf(" %[^\n]", estudiante.celular);

      printf("\n\tIngrese la edad:");fflush(stdin);
      scanf(" %[^\n]", estudiante.edad);

      // Inicializar los programas del estudiante.
      int i = 0, j = 0;
      for(i = 0; i < 4; i++) {
        strcpy(estudiante.infoprog[i].nombrePrograma, "null"); //nombre
        strcpy(estudiante.infoprog[i].codigoPrograma, "null"); //codigo
        // Inicializar materias del programa
        for(j = 0; j < 4; j++) {
          strcpy(estudiante.infoprog[i].materias[j].nombreMateria, "null");
          strcpy(estudiante.infoprog[i].materias[j].codigoMateria, "null");
          strcpy(estudiante.infoprog[i].materias[j].nombreProfesor, "null");
          strcpy(estudiante.infoprog[i].materias[j].periodoaca, "null");
          estudiante.infoprog[i].materias[j].parcial1 = 0.0;
          estudiante.infoprog[i].materias[j].parcial2 = 0.0;
          estudiante.infoprog[i].materias[j].parcial3 = 0.0;
          estudiante.infoprog[i].materias[j].parcial4 = 0.0;
          estudiante.infoprog[i].materias[j].definitiva = 0.0;
        }
      }
      return estudiante;
    }
    else {
      printf("\tEL ESTUDIANTE YA ESTA REGISTRADO!\n");
      strcpy(estudiante.nombre, "null");
      return estudiante;
    }
  }
}

// Funcion para guardar en archivo un objeto estudiante
// recibe como parametros un un objeto estudiante que es resultado de la Funcion
// crearEstudiante(..), y recibe también el nombre del archivo
void guardarEstudiante(Estudiante estudiante, char* nombreArchivo) {
  // Abrir el archivo en modo "a" y de forma binaria "ab"
  FILE* file = fopen(nombreArchivo, "ab");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    // Si nombre es igual a null, quiere decir que el usuario ya existe
    if(strcmp(estudiante.nombre, "null") != 0) {
      fwrite(&estudiante, sizeof(Estudiante), 1, file);
      printf("\tEstudiante guardado\n");
    }
    pausar();
    fclose(file);
  }
}

// Funcion que muestra ordenadamente todos los estudiantes que estan registrados
// mostrando ademas los programas en los que esta matriculados, con sus respectivas
// materias.
void mostrarEstudiante(char* nombreArchivo) {
  // Solo queremos visualizar los datos, por eso abrimos en modo lectura
  FILE* file = fopen(nombreArchivo, "rb");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    Estudiante estudiante; // Objeto que contendrá a estudiante
    while( fread(&estudiante, sizeof(Estudiante), 1, file)) {
      printf("-------------------------------------\n");
      printf("Estado:     %s\n", estudiante.estado);
      printf("Codigo:     %s\n", estudiante.codigo);
      printf("Nombre:     %s\n", estudiante.nombre);
      printf("Apelllido:  %s\n", estudiante.apellido);
      printf("Celular:    %s\n", estudiante.celular);
      printf("Edad:       %s\n", estudiante.edad);
      // Mostrar los programas:
      printf("Programas: \n");
      int i = 0;
      for(i = 0; i < 4; i++) {
        // Solo imprimimos los programas que tenga contenido, los que no tienen estan en "null"
        if (strcmp(estudiante.infoprog[i].codigoPrograma, "null") != 0) {
          printf("\t%d. %s-%s\n", i+1, estudiante.infoprog[i].codigoPrograma, estudiante.infoprog[i].nombrePrograma);
          // Mostrar las materias de un pograma
          int j = 0;
          printf("\t   -> Materias:\n");
          for(j = 0; j < 4; j++) {
            // Solo imprimimos las materias que tengan contenido, las que no tienen estan en "null"
            if (strcmp(estudiante.infoprog[i].materias[j].codigoMateria, "null") != 0) {
              printf("\t\t%d. %s - %s, nota: %0.2f\n", j+1,estudiante.infoprog[i].materias[j].codigoMateria,
                                                        estudiante.infoprog[i].materias[j].nombreMateria,
                                                        estudiante.infoprog[i].materias[j].definitiva);
            }
          }
        }
      }
      pausar();
    }
  }
}

// Funcion que permite modificar el valor del telefono de un estudiante, asi como
// modificar el estado: pasar de activo a inactivo, y viceversa
void modificarEstudiante(char* nombreArchivo) {
  // Necesitamos modificar el archivo abrimos en modo lectura y escritura - binario
  FILE* file = fopen(nombreArchivo, "rb+");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    Estudiante estudiante; // Objeto que contendra el estudiante
    // Recibimos codigo por teclado
    char codigo[11];
    printf("Codigo del estudiante: ");fflush(stdin);
    scanf(" %[^\n]", codigo);

    // Guarda la direccion fisica del estudiante
    int dir_fisica;
    while( fread(&estudiante, sizeof(Estudiante), 1, file)) {
      if( strcmp(codigo, estudiante.codigo) == 0) {
        // Se guarda la direccion fisica donde termina el estudiante, necesitamos
        // saber dond empieza no donde acaba, por eso le restamos sizeof(Estudiante)
        // para que nos ubique al comienzo
        dir_fisica = ftell(file) - sizeof(Estudiante);

        printf("Estudiante %s %s estado: %s\n", estudiante.nombre, estudiante.apellido, estudiante.estado);

        printf("\tIngrese el nuevo celular: ");fflush(stdin);
        scanf(" %[^\n]", estudiante.celular);
        getchar();
        printf("\tDesea cambiar el estado? (s/n)\n");fflush(stdin);
        char cambiar;
        scanf("%c", &cambiar);

        if(cambiar == 's') {
          if(strcmp(estudiante.estado, "activo") == 0)
            strcpy(estudiante.estado, "inactivo");
          else
            strcpy(estudiante.estado, "activo");
        }
        fseek(file, (long)(dir_fisica), 0);
        fwrite(&estudiante, sizeof(Estudiante), 1, file);
        fclose(file);
        break;
      }
    }
  }
}

// Funcion que permite agregar un programa academico a un estudiante en especifico
void agregarPrograma(char* nombreArchivo) {
  FILE* file = fopen(nombreArchivo, "rb+");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    Estudiante estudiante;
    char codigo[11];
    printf("Codigo del estudiante: ");fflush(stdin);
    scanf(" %[^\n]", codigo);

    int dir_fisica;
    while( fread(&estudiante, sizeof(Estudiante), 1, file)) {
      // Si el codigo ingresado por teclado coincide con el del objeto estudiante y ademas este
      // es activo, puede agregar programas
      if( (strcmp(codigo, estudiante.codigo) == 0) && (strcmp(estudiante.estado, "activo") == 0)) {
        dir_fisica = ftell(file) - sizeof(Estudiante);
        // Recorrer los programas
        int i = 0;
        for(i = 0; i < 4; i++) {
          if (strcmp(estudiante.infoprog[i].codigoPrograma, "null") == 0) {
            printf("Añadir programa\n");
            printf("\tCodigo Programa: "); fflush(stdin);
            scanf(" %[^\n]", estudiante.infoprog[i].codigoPrograma);
            printf("\tNombre Programa: "); fflush(stdin);
            scanf(" %[^\n]", estudiante.infoprog[i].nombrePrograma);
            printf("\tCantidad de Semestre?: "); fflush(stdin);
            scanf("%d", &estudiante.infoprog[i].semestres);
          }
          else {
            printf("\t* %s - %s\n", estudiante.infoprog[i].codigoPrograma, estudiante.infoprog[i].nombrePrograma);
          }
          getchar();
          printf("Desea agregar otro programa? (s/n)");
          char otro;
          scanf("%c", &otro);

          if(otro != 's') {
            i = 4;
            break;
          }
        }
        fseek(file, (long)(dir_fisica), 0);
        fwrite(&estudiante, sizeof(Estudiante), 1, file);
        fclose(file);
        break;
      }
    }
  }
}

// Funcion que permite agregar una materia a un programa de un estudiante especifico
void agregarMateria(char* nombreArchivo) {
  FILE* file = fopen(nombreArchivo, "rb+");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    Estudiante estudiante;
    char codigo[11];
    char codigoPrograma[5];
    printf("Codigo del estudiante: ");fflush(stdin);
    scanf(" %[^\n]", codigo);

    int dir_fisica;
    while( fread(&estudiante, sizeof(Estudiante), 1, file)) {
      // Si el codigo ingresado por teclado coincide con el del objeto estudiante y ademas este
      // es activo, puede agregar materias
      if( (strcmp(codigo, estudiante.codigo) == 0) && (strcmp(estudiante.estado, "activo") == 0)) {
        dir_fisica = ftell(file) - sizeof(Estudiante);
        printf("Codigo del programa: ");
        scanf(" %[^\n]", codigoPrograma);
        // Recorrer los programas
        int i = 0;
        for(i = 0; i < 4; i++) {
          // Se compara el codigoPrograma ingresado por teclado con el codigoPrograma del objeto estudiante
          if (strcmp(estudiante.infoprog[i].codigoPrograma, codigoPrograma) == 0) {
            int j = 0;
            for(j = 0; j < 4; j++) {
              if (strcmp(estudiante.infoprog[i].materias[j].codigoMateria, "null") == 0) {
                printf("Añadir Materia\n");

                printf("\tCodigo Materia: "); fflush(stdin);
                scanf(" %[^\n]", estudiante.infoprog[i].materias[j].codigoMateria);
                printf("\tNombre Materia: "); fflush(stdin);
                scanf(" %[^\n]", estudiante.infoprog[i].materias[j].nombreMateria);
                printf("\tNombre profesor: "); fflush(stdin);
                scanf(" %[^\n]", estudiante.infoprog[i].materias[j].nombreProfesor);
                printf("\tPeriodo academico: "); fflush(stdin);
                scanf(" %[^\n]", estudiante.infoprog[i].materias[j].periodoaca);
                // Leer por teclado las notas parciales
                float p1, p2, p3, p4;
                printf("\tNota parcial 1: "); fflush(stdin);
                scanf("%f", &p1);
                printf("\tNota parcial 2: "); fflush(stdin);
                scanf("%f", &p2);
                printf("\tNota parcial 3: "); fflush(stdin);
                scanf("%f", &p3);
                printf("\tNota parcial 4: "); fflush(stdin);
                scanf("%f", &p4);
                estudiante.infoprog[i].materias[j].parcial1 = p1;
                estudiante.infoprog[i].materias[j].parcial2 = p2;
                estudiante.infoprog[i].materias[j].parcial3 = p3;
                estudiante.infoprog[i].materias[j].parcial4 = p4;
                // Calcular nota definitiva de la materia:
                float definitiva = p1*0.1 + p2*0.2 + p3*0.3 + p4*0.4;
                estudiante.infoprog[i].materias[j].definitiva = definitiva;

              }
              else {
                printf("\t*.%s - %s", estudiante.infoprog[i].materias[j].codigoMateria, estudiante.infoprog[i].materias[j].nombreMateria);
              }
              getchar();
              printf("\nDesea agregar otra materia? (s/n): ");
              char otro;
              scanf("%c", &otro);

              if(otro != 's') {
                j = 4;
                break;
              }
            }
            fseek(file, (long)(dir_fisica), 0);
            fwrite(&estudiante, sizeof(Estudiante), 1, file);
            fclose(file);
            break;
          }
        }
      }
    }
  }
}

// Funcion que muestra el historial de las materias reprobadas (nota < 3)
void historialAcademico(char* nombreArchivo) {
  FILE* file = fopen(nombreArchivo, "rb");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    Estudiante estudiante;
    char codigo[11];
    char codigoPrograma[5];
    printf("Codigo del estudiante: ");fflush(stdin);
    scanf(" %[^\n]", codigo);

    int dir_fisica;
    while( fread(&estudiante, sizeof(Estudiante), 1, file)) {
      if( strcmp(codigo, estudiante.codigo) == 0) {
        dir_fisica = ftell(file) - sizeof(Estudiante);
        printf("Codigo del programa: ");
        scanf(" %[^\n]", codigoPrograma);
        printf("Estudiante %s %s - estado: %s\n", estudiante.nombre, estudiante.apellido, estudiante.estado);
        // Recorrer los programas
        int i = 0;
        for(i = 0; i < 4; i++) {
          // Se compara el codigoPrograma ingresado por teclado con el codigoPrograma del objeto estudiante
          if (strcmp(estudiante.infoprog[i].codigoPrograma, codigoPrograma) == 0) {
            int j = 0;
            printf("Materias reprobadas\n");
            for(j = 0; j < 4; j++) {
              // Buscar materias que esten por debajo de 4.0 y además que sean diferentes de null
              if (estudiante.infoprog[i].materias[j].definitiva < 3 && strcmp(estudiante.infoprog[i].materias[j].codigoMateria, "null")!=0) {
                printf("\n---------------------------------------\n");
                printf("\t\t*. %s - ", estudiante.infoprog[i].materias[j].codigoMateria);
                printf("%s\n", estudiante.infoprog[i].materias[j].nombreMateria);
                printf("\t\tNota: %0.2f\n", estudiante.infoprog[i].materias[j].definitiva);
                printf("\t\tPeriodo: %s\n", estudiante.infoprog[i].materias[j].periodoaca);
                printf("\t\tDocente: %s\n", estudiante.infoprog[i].materias[j].nombreProfesor);
              }
            }
            pausar();
          }
        }
        fclose(file);
        break;
      }
    }
  }
}

// Funcion que muestra las personas inactivas de un programa
void inactivosPrograma(char* nombreArchivo) {
  FILE* file = fopen(nombreArchivo, "rb");

  if (file == NULL) {
    printf("Error al abrir el archivo ... \n");
    pausar();
  }
  else {
    Estudiante estudiante;
    char codigoPrograma[5];
    printf("Codigo del Programa: ");fflush(stdin);
    scanf(" %[^\n]", codigoPrograma);

    int cant = 0;
    printf("ESTUDIANTES INACTIVOS DE %s", codigoPrograma);
    while( fread(&estudiante, sizeof(Estudiante), 1, file)) {
      // Recorrer programas de estudiante.
      int i = 0;
      for(i = 0; i < 4; i++) {
        if ( (strcmp(codigoPrograma, estudiante.infoprog[i].codigoPrograma) == 0) && (strcmp(estudiante.estado, "inactivo") == 0)) {
          cant = cant + 1;
          printf("\n---------------------------------------\n");
          printf("\t%d.\n", cant);
          printf("\t   Codigo:   %s\n", estudiante.codigo);
          printf("\t   Nombre:   %s\n", estudiante.nombre);
          printf("\t   Apellido: %s\n", estudiante.apellido);
          printf("\t   Celular:  %s\n", estudiante.celular);
        }
      }
      pausar();
    }
    fclose(file);
  }
}

// Muestra el menu por pantalla y permite seleccionar una opcion
void menu(char* nombreArchivo) {
  int opcion;

  do {
    system("clear");
    printf("1. Agregar estudiante\n");
    printf("2. Mostrar estudiantes\n");
    printf("3. Modificar estudiante\n");
    printf("4. Agregar Programa a estudiante\n");
    printf("5. Agregar materia a estudiante\n");
    printf("6. Historial materias reprobadas\n");
    printf("7. Inactivos de un programa\n");
    printf("8. Salir");
    printf("\n\tIngrese opcion: ");
    scanf("%d", &opcion);
    if (opcion > 0 && opcion < 9) {
      system("clear");
      switch (opcion) {
        case 1:
          guardarEstudiante(crearEstudiante(nombreArchivo), nombreArchivo);
          break;
        case 2:
          mostrarEstudiante(nombreArchivo);
          break;
        case 3:
          modificarEstudiante(nombreArchivo);
          break;
        case 4:
          agregarPrograma(nombreArchivo);
          break;
        case 5:
          agregarMateria(nombreArchivo);
          break;
        case 6:
          historialAcademico(nombreArchivo);
          break;
        case 7:
          inactivosPrograma(nombreArchivo);
          break;
        case 8:
          printf("Fin del programa\n");
          pausar();
          break;
      }
    }

  } while(opcion != 8);
}


int main() {
  char nombreArchivo[12] = "datos.bin";

  menu(nombreArchivo);
  return 0;
}
