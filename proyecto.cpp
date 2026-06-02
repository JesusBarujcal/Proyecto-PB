#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;


// ============================================================
// ESTRUCTURAS
// ============================================================

struct Usuario {
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena;
    string direccion;
    string metodoDePago;
};

struct Producto {
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

struct Comentario {
    int idComentario;
    string productoNombre;
    string usuarioNombre;
    string texto;
    string fecha;
};

struct ItemCarrito {
    Producto producto;
    int cantidad;
};

struct Carrito {
    int idCarrito;
    int idUsuario;
    vector<ItemCarrito> items;
    bool pagado;
};

struct OrdenDeCompra {
    int idOrden;
    Usuario usuario;
    vector<ItemCarrito> productos;
    double subtotal;
    double impuestos;
    double envio;
    double total;
};

// ============================================================
// VARIABLES GLOBALES
// ============================================================

vector<Usuario> usuarios;
vector<Producto> productos;
vector<Comentario> comentarios;
vector<Carrito> carritosGlobales;
vector<OrdenDeCompra> ordenes;

int proximoIdCarrito = 1;
int proximoIdOrden = 1;

// ============================================================
// UTILIDADES
// ============================================================


string aMayusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = toupper((unsigned char)texto[i]);
    }
    return texto;
}

double calcularSubtotal(const vector<ItemCarrito>& items) {
    double subtotal = 0.0;
    for (size_t i = 0; i < items.size(); i++) {
        subtotal += items[i].producto.precio * items[i].cantidad;
    }
    return subtotal;
}

// ============================================================
// AGREGAR DATOS
// ============================================================

void addU(int id, string nom, string corr, string contra, string dir, string pago) {
    Usuario u;
    u.idUsuario = id;
    u.nombre = nom;
    u.correoElectronico = corr;
    u.contrasena = contra;
    u.direccion = dir;
    u.metodoDePago = pago;
    usuarios.push_back(u);
}

void addP(int id, string nom, string desc, double pre, int stk) {
    Producto p;
    p.idProducto = id;
    p.nombre = nom;
    p.descripcion = desc;
    p.precio = pre;
    p.stock = stk;
    productos.push_back(p);
}

void addC(int id, string pNom, string uNom, string txt, string f) {
    Comentario c;
    c.idComentario = id;
    c.productoNombre = pNom;
    c.usuarioNombre = uNom;
    c.texto = txt;
    c.fecha = f;
    comentarios.push_back(c);
}

void cargarDatos() {
    // Usuarios
    addU(1, "Juan Perez", "juan.perez@email.com", "Qwerty123", "Carrera 45 #10-20", "Tarjeta de credito");
    addU(2, "Ana Gomez", "ana.gomez@email.com", "Pass456", "Calle 21 #35-50", "PayPal");
    addU(3, "Carlos Ruiz", "carlos.ruiz@email.com", "Segura789", "Avenida Principal #100", "Transferencia bancaria");
    addU(4, "Sofia Martinez", "sofia.martinez@email.com", "Clave987", "Calle 8 #20-30", "Efectivo");
    addU(5, "Diego Fernandez", "diego.fernandez@email.com", "Contra654", "Carrera 77 #40-60", "Tarjeta debito");

    // Productos
    string nombres[] = {
        "Laptop","Smartphone","Tablet","Auriculares","Teclado",
        "Mouse","Monitor","Impresora","Camara","Smartwatch",
        "Silla Gamer","Microondas","Refrigerador","Lavadora","Cafetera",
        "Drone","Bocina Bluetooth","Videocamara","TV LED","Bateria Externa",
        "Disco Duro","Memoria USB","Router","Joystick","Fuente de Poder",
        "SSD","Altavoces","Webcam","Procesador","Motherboard",
        "Memoria RAM","Fuente Solar","Control Remoto","Termostato","Smart Lock",
        "Proyector","Switch Ethernet","Reloj Digital","Luces LED","Estabilizador",
        "Cargador Inalambrico","HDD Externo","Microfono","Altavoz Inteligente","Antena Wi-Fi",
        "Climatizador","Raspberry Pi","Capturadora","Smart Plug","Timbre Inteligente"
    };

    string descripciones[] = {
        "Portatil con pantalla Full HD y SSD de 512GB",
        "Telefono con camara de 108MP y carga rapida",
        "Dispositivo con pantalla tactil de 10 pulgadas",
        "Audifonos inalambricos con cancelacion de ruido",
        "Teclado mecanico con iluminacion RGB",
        "Raton inalambrico con sensor optico de alta precision",
        "Pantalla LED 4K de 27 pulgadas",
        "Laser multifuncional con Wi-Fi",
        "Camara digital con lente profesional",
        "Reloj inteligente con GPS y monitoreo cardiaco",
        "Silla ergonomica ajustable con soporte lumbar",
        "Horno microondas con multiples funciones",
        "Frigorifico doble puerta con sistema No Frost",
        "Lavadora automatica con capacidad de 10kg",
        "Cafetera express con vaporizador de leche",
        "Drone con camara 4K y estabilizador",
        "Altavoz portatil con sonido envolvente",
        "Videocamara profesional con grabacion en 4K",
        "Televisor inteligente de 55 pulgadas con HDR",
        "Bateria de 20000mAh con carga rapida",
        "Disco duro externo de 2TB",
        "Pendrive de 128GB",
        "Router Wi-Fi 6 de alta velocidad",
        "Control inalambrico para videojuegos",
        "Fuente de alimentacion para PC de 750W",
        "Unidad de almacenamiento SSD de 1TB",
        "Par de bocinas estereo con subwoofer",
        "Camara web Full HD con microfono integrado",
        "CPU Intel i7 de ultima generacion",
        "Placa base compatible con procesadores modernos",
        "Modulo de RAM DDR4 de 16GB",
        "Panel solar portatil con bateria integrada",
        "Mando universal para TV y dispositivos",
        "Termostato digital programable",
        "Cerradura electronica con huella digital",
        "Proyector LED con resolucion Full HD",
        "Switch de red de 8 puertos",
        "Reloj inteligente con pantalla AMOLED",
        "Tiras LED RGB con control remoto",
        "Estabilizador de voltaje para dispositivos electronicos",
        "Base de carga inalambrica rapida",
        "Disco duro portatil de 4TB",
        "Microfono profesional para grabacion",
        "Asistente de voz con altavoz integrado",
        "Amplificador de senal inalambrico",
        "Aire acondicionado portatil con control remoto",
        "Kit de desarrollo con Raspberry Pi 4",
        "Placa de captura de video en alta resolucion",
        "Enchufe inteligente compatible con asistentes virtuales",
        "Timbre con camara y conexion a Wi-Fi"
    };

    double precios[] = {
        89999,49950,29999,12999,8999,
        5999,49900,17999,79999,19999,
        29999,12999,119999,59999,14999,
        69999,8999,99999,74999,3999,
        12999,2999,19999,7999,8999,
        14999,13999,6999,34999,19999,
        7999,24999,2499,9999,19999,
        29999,5999,8999,3999,15999,
        4999,17999,14999,12999,7999,
        29999,12999,19999,3999,14999
    };

    int stocks[] = {
        10,20,15,25,30,
        50,12,18,8,22,
        14,40,5,7,35,
        9,33,6,11,45,
        28,60,16,20,17,
        32,23,37,9,13,
        41,4,50,22,6,
        12,38,26,55,10,
        30,15,7,20,33,
        5,19,8,42,10
    };

    for (int i = 0; i < 50; i++) {
        addP(i + 1, nombres[i], descripciones[i], precios[i], stocks[i]);
    }

    // Comentarios
    addC(1,  "Laptop", "Juan Perez", "Excelente rendimiento; muy rapida. Me encanta.", "2025-05-01");
    addC(2,  "Smartphone", "Ana Gomez", "Buena camara pero la bateria dura poco.", "2025-05-03");
    addC(3,  "Tablet", "Carlos Ruiz", "No me gusto; pantalla de baja calidad.", "2025-05-05");
    addC(4,  "Auriculares", "Sofia Martinez", "Sonido aceptable pero el material parece fragil.", "2025-05-06");
    addC(5,  "Teclado", "Diego Fernandez", "Muy buen teclado mecanico; excelente respuesta.", "2025-05-08");
    addC(6,  "Mouse", "Ana Gomez", "El sensor no es tan preciso como esperaba.", "2025-05-10");
    addC(7,  "Monitor", "Carlos Ruiz", "Colores vibrantes y buena resolucion. Muy satisfecho.", "2025-05-12");
    addC(8,  "Impresora", "Juan Perez", "Tarda mucho en imprimir; no me convence.", "2025-05-13");
    addC(9,  "Camara", "Sofia Martinez", "Increible calidad de imagen; fotos super nitidas.", "2025-05-15");
    addC(10, "Smartwatch", "Diego Fernandez", "Buena bateria; pero la pantalla no es muy brillante.", "2025-05-18");
    addC(11, "Silla Gamer", "Lucia Rodriguez", "Comodidad espectacular; perfecto para largas sesiones.", "2025-05-20");
    addC(12, "Microondas", "Andres Ramirez", "Calienta bien pero hace mucho ruido.", "2025-05-22");
    addC(13, "Refrigerador", "Maria Garcia", "Espacioso y enfria rapido; muy recomendado.", "2025-05-24");
    addC(14, "Lavadora", "Javier Martinez", "Lava bien pero el ciclo es muy largo.", "2025-05-26");
    addC(15, "Cafetera", "Carolina Lopez", "Hace cafe delicioso; facil de usar.", "2025-05-28");
    addC(16, "Drone", "Daniel Castro", "Muy divertido pero la bateria dura poco.", "2025-05-30");
    addC(17, "Bocina Bluetooth", "Paola Herrera", "Sonido potente y buena conexion Bluetooth.", "2025-06-01");
    addC(18, "Videocamara", "Esteban Rojas", "Perfecta para grabaciones profesionales.", "2025-06-03");
    addC(19, "TV LED", "Fernanda Sanchez", "Imagen excelente pero el sonido podria mejorar.", "2025-06-05");
    addC(20, "Bateria Externa", "Camilo Torres", "Carga bien pero es un poco pesada.", "2025-06-07");
}

void mostrarCatalogo() {
    cout << "\n===== CATALOGO DE PRODUCTOS =====\n";
    cout << left
         << setw(4)  << "ID"
         << setw(22) << "Nombre"
         << setw(12) << "Precio"
         << setw(7)  << "Stock"
         << endl;
    cout << string(50, '-') << endl;

    for (size_t i = 0; i < productos.size(); i++) {
        cout << left
             << setw(4)  << productos[i].idProducto
             << setw(22) << productos[i].nombre
             << "$" << setw(11) << fixed << setprecision(2) << productos[i].precio
             << setw(7)  << productos[i].stock
             << endl;
    }
}

Usuario* buscarUsuarioPorId(int id) {
    for (size_t i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].idUsuario == id) {
            return &usuarios[i];
        }
    }
    return NULL;
}

Producto* buscarProductoPorId(int id) {
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].idProducto == id) {
            return &productos[i];
        }
    }
    return NULL;
}

int contarCarritosActivos(int idUsuario) {
    int cnt = 0;
    for (size_t i = 0; i < carritosGlobales.size(); i++) {
        if (carritosGlobales[i].idUsuario == idUsuario && !carritosGlobales[i].pagado) {
            cnt++;
        }
    }
    return cnt;
}

int buscarCarritoPorIdYUsuario(int idCarrito, int idUsuario) {
    for (size_t i = 0; i < carritosGlobales.size(); i++) {
        if (carritosGlobales[i].idCarrito == idCarrito && carritosGlobales[i].idUsuario == idUsuario) {
            return (int)i;
        }
    }
    return -1;
}

int buscarCarritoActivo(int idCarrito, int idUsuario) {
    int idx = buscarCarritoPorIdYUsuario(idCarrito, idUsuario);
    if (idx != -1 && !carritosGlobales[idx].pagado) {
        return idx;
    }
    return -1;
}

void listarCarritosUsuario(int idUsuario) {
    cout << "\n--- CARROS DEL USUARIO ---\n";
    bool hay = false;

    for (size_t i = 0; i < carritosGlobales.size(); i++) {
        if (carritosGlobales[i].idUsuario == idUsuario) {
            hay = true;
            cout << "Carrito #" << carritosGlobales[i].idCarrito
                 << " | items: " << carritosGlobales[i].items.size()
                 << " | estado: " << (carritosGlobales[i].pagado ? "PAGADO" : "ACTIVO")
                 << endl;
        }
    }

    if (!hay) {
        cout << "Este usuario no tiene carritos.\n";
    }
}

int crearCarrito(int idUsuario) {
    if (contarCarritosActivos(idUsuario) >= 2) {
        cout << "[!] El usuario ya tiene 2 carritos activos. Pague uno primero.\n";
        return -1;
    }

    Carrito c;
    c.idCarrito = proximoIdCarrito++;
    c.idUsuario = idUsuario;
    c.pagado = false;
    carritosGlobales.push_back(c);

    cout << "[+] Carrito #" << c.idCarrito << " creado correctamente.\n";
    return c.idCarrito;
}

void listarCarrito(int idCarrito, int idUsuario) {
    int idx = buscarCarritoPorIdYUsuario(idCarrito, idUsuario);
    if (idx == -1) {
        cout << "[!] Carrito no encontrado.\n";
        return;
    }

    Carrito& c = carritosGlobales[idx];
    Usuario* u = buscarUsuarioPorId(idUsuario);

    cout << "\n===== CARRITO #" << c.idCarrito << " =====\n";
    cout << "Usuario: " << (u ? u->nombre : "Desconocido") << endl;
    cout << "Estado : " << (c.pagado ? "PAGADO" : "ACTIVO") << endl;

    if (c.items.empty()) {
        cout << "(Carrito vacio)\n";
        return;
    }

    cout << left
         << setw(4)  << "ID"
         << setw(22) << "Nombre"
         << setw(8)  << "Cant."
         << setw(12) << "P.Unit."
         << "Subtotal\n";
    cout << string(55, '-') << endl;

    double subtotal = 0.0;
    for (size_t i = 0; i < c.items.size(); i++) {
        const ItemCarrito& it = c.items[i];
        double sub = it.producto.precio * it.cantidad;
        subtotal += sub;

        cout << left
             << setw(4)  << it.producto.idProducto
             << setw(22) << it.producto.nombre
             << setw(8)  << it.cantidad
             << "$" << setw(11) << fixed << setprecision(2) << it.producto.precio
             << "$" << fixed << setprecision(2) << sub << endl;
    }

    cout << string(55, '-') << endl;
    cout << right << setw(48) << "SUBTOTAL: $" << fixed << setprecision(2) << subtotal << endl;
}

void agregarAlCarrito(int idCarrito, int idUsuario) {
    int idx = buscarCarritoActivo(idCarrito, idUsuario);
    if (idx == -1) {
        cout << "[!] Carrito invalido o ya pagado.\n";
        return;
    }

    mostrarCatalogo();

    int idProducto;
    int cantidad;

    cout << "ID del producto: ";
    cin >> idProducto;
    cout << "Cantidad: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "[!] La cantidad debe ser mayor que cero.\n";
        return;
    }

    Producto* p = buscarProductoPorId(idProducto);
    if (!p) {
        cout << "[!] Producto no encontrado.\n";
        return;
    }

    if (p->stock < cantidad) {
        cout << "[!] Stock insuficiente. Stock disponible: " << p->stock << endl;
        return;
    }

    for (size_t i = 0; i < carritosGlobales[idx].items.size(); i++) {
        if (carritosGlobales[idx].items[i].producto.idProducto == idProducto) {
            carritosGlobales[idx].items[i].cantidad += cantidad;
            p->stock -= cantidad;
            cout << "[+] Se actualizo la cantidad de " << p->nombre << " en el carrito.\n";
            return;
        }
    }

    ItemCarrito item;
    item.producto = *p;
    item.cantidad = cantidad;
    carritosGlobales[idx].items.push_back(item);
    p->stock -= cantidad;

    cout << "[+] Producto agregado correctamente al carrito.\n";
    cout << "Stock restante: " << p->stock << endl;
}

void generarOrdenTxt(const OrdenDeCompra& o) {
    ostringstream nombreArchivo;
    nombreArchivo << "orden_" << o.idOrden << "_usuario_" << o.usuario.idUsuario << ".txt";

    ofstream archivo(nombreArchivo.str().c_str());
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo crear el archivo de orden.\n";
        return;
    }

    archivo << "========================================\n";
    archivo << "             ORDEN DE COMPRA\n";
    archivo << "========================================\n";
    archivo << "ID ORDEN : " << o.idOrden << "\n";
    archivo << "USUARIO  : " << o.usuario.idUsuario << "\n";
    archivo << "NOMBRE   : " << o.usuario.nombre << "\n";
    archivo << "CORREO   : " << o.usuario.correoElectronico << "\n";
    archivo << "DIRECCION: " << o.usuario.direccion << "\n";
    archivo << "PAGO     : " << o.usuario.metodoDePago << "\n";
    archivo << "----------------------------------------\n";
    archivo << "PRODUCTOS\n";
    archivo << left
            << setw(4)  << "ID"
            << setw(22) << "Nombre"
            << setw(8)  << "Cant."
            << setw(12) << "P.Unit."
            << "Subtotal\n";
    archivo << string(55, '-') << "\n";

    for (size_t i = 0; i < o.productos.size(); i++) {
        const ItemCarrito& it = o.productos[i];
        double sub = it.producto.precio * it.cantidad;

        archivo << left
                << setw(4)  << it.producto.idProducto
                << setw(22) << it.producto.nombre
                << setw(8)  << it.cantidad
                << "$" << setw(11) << fixed << setprecision(2) << it.producto.precio
                << "$" << fixed << setprecision(2) << sub << "\n";
    }

    archivo << string(55, '-') << "\n";
    archivo << right << setw(45) << "SUBTOTAL : $" << fixed << setprecision(2) << o.subtotal << "\n";
    archivo << right << setw(45) << "IMPUESTOS : $" << fixed << setprecision(2) << o.impuestos << "\n";
    archivo << right << setw(45) << "ENVIO     : $" << fixed << setprecision(2) << o.envio << "\n";
    archivo << right << setw(45) << "TOTAL     : $" << fixed << setprecision(2) << o.total << "\n";
    archivo << "========================================\n";
    archivo << "Gracias por su compra!\n";
    archivo << "========================================\n";

    archivo.close();
    cout << "[+] Orden generada: " << nombreArchivo.str() << endl;
}

void pagarCarrito(int idCarrito, int idUsuario) {
    int idx = buscarCarritoActivo(idCarrito, idUsuario);
    if (idx == -1) {
        cout << "[!] Carrito invalido o ya pagado.\n";
        return;
    }

    Carrito& c = carritosGlobales[idx];
    if (c.items.empty()) {
        cout << "[!] El carrito esta vacio. Agrega productos primero.\n";
        return;
    }

    Usuario* u = buscarUsuarioPorId(idUsuario);
    if (!u) {
        cout << "[!] Usuario no encontrado.\n";
        return;
    }

    OrdenDeCompra o;
    o.idOrden = proximoIdOrden++;
    o.usuario = *u;
    o.productos = c.items;

    o.subtotal = calcularSubtotal(o.productos);
    o.impuestos = o.subtotal * 0.19;
    o.envio = (o.subtotal >= 500000.0) ? 0.0 : 15000.0;
    o.total = o.subtotal + o.impuestos + o.envio;

    ordenes.push_back(o);
    c.pagado = true;

    cout << "\n[=] RESUMEN DE LA ORDEN #" << o.idOrden << "\n";
    cout << "    Subtotal : $" << fixed << setprecision(2) << o.subtotal << "\n";
    cout << "    Impuestos: $" << fixed << setprecision(2) << o.impuestos << "\n";
    cout << "    Envio    : $" << fixed << setprecision(2) << o.envio << "\n";
    cout << "    TOTAL    : $" << fixed << setprecision(2) << o.total << "\n";

    generarOrdenTxt(o);
}

int login() {
    string correo, clave;

    cout << "Correo: ";
    cin >> correo;
    cout << "Contrasena: ";
    cin >> clave;

    for (size_t i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].correoElectronico == correo &&
            usuarios[i].contrasena == clave) {
            return usuarios[i].idUsuario;
        }
    }
    return -1;
}

void listarStockBajo() {
    cout << "\n--- PRODUCTOS CON STOCK MENOR A 15 ---\n";
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].stock < 15) {
            cout << productos[i].idProducto << ". "
                 << productos[i].nombre << " - Stock: "
                 << productos[i].stock << endl;
        }
    }
}

void listarComentariosDesdeFecha() {
    string fecha;
    cout << "Ingrese fecha (YYYY-MM-DD): ";
    cin >> fecha;

    cout << "\n--- COMENTARIOS DESDE " << fecha << " ---\n";
    for (size_t i = 0; i < comentarios.size(); i++) {
        if (comentarios[i].fecha >= fecha) {
            cout << "[" << comentarios[i].fecha << "] "
                 << comentarios[i].productoNombre << " - "
                 << comentarios[i].usuarioNombre << ": "
                 << comentarios[i].texto << endl;
        }
    }
}

void listarUsuarios() {
    cout << "\n--- USUARIOS ---\n";
    for (size_t i = 0; i < usuarios.size(); i++) {
        cout << "ID: " << usuarios[i].idUsuario
             << " | NOMBRE: " << aMayusculas(usuarios[i].nombre)
             << " | CORREO: " << usuarios[i].correoElectronico << endl;
    }
}

void menuCarrito(int idUsuario) {
    Usuario* u = buscarUsuarioPorId(idUsuario);
    if (!u) {
        cout << "[!] Usuario no encontrado.\n";
        return;
    }

    int opcion;
    do {
        cout << "\n----- MENU CARRITO | " << u->nombre << " -----\n";
        cout << "Carritos activos: " << contarCarritosActivos(idUsuario) << "/2\n";
        listarCarritosUsuario(idUsuario);

        cout << "\n1. Crear nuevo carrito\n";
        cout << "2. Ver productos de un carrito\n";
        cout << "3. Agregar producto a carrito\n";
        cout << "4. Pagar carrito (genera orden)\n";
        cout << "5. Ver catalogo completo\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            crearCarrito(idUsuario);
            system("pause");
        }
        else if (opcion == 2) {
            int idC;
            cout << "Numero de carrito: ";
            cin >> idC;
            listarCarrito(idC, idUsuario);
            system("pause");
        }
        else if (opcion == 3) {
            int idC;
            cout << "Numero de carrito: ";
            cin >> idC;
            agregarAlCarrito(idC, idUsuario);
            system("pause");
        }
        else if (opcion == 4) {
            int idC;
            cout << "Numero de carrito a pagar: ";
            cin >> idC;
            pagarCarrito(idC, idUsuario);
            system("pause");
        }
        else if (opcion == 5) {
            mostrarCatalogo();
            system("pause");
        }
    } while (opcion != 0);
}

void menuPrincipal() {
    int opcion;
    do {
        cout << "\n========== TIENDA ONLINE ==========\n";
        cout << "1. Seleccionar usuario\n";
        cout << "2. Ver catalogo completo\n";
        cout << "3. Ver usuarios\n";
        cout << "4. Ver productos con stock menor a 15\n";
        cout << "5. Ver comentarios desde una fecha\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\n--- USUARIOS DISPONIBLES ---\n";
            for (size_t i = 0; i < usuarios.size(); i++) {
                cout << "  [" << usuarios[i].idUsuario << "] "
                     << usuarios[i].nombre << endl;
            }
            cout << "ID de usuario: ";
            int id;
            cin >> id;
            menuCarrito(id);
        }
        else if (opcion == 2) {
            mostrarCatalogo();
            system("pause");
        }
        else if (opcion == 3) {
            listarUsuarios();
            system("pause");
        }
        else if (opcion == 4) {
            listarStockBajo();
            system("pause");
        }
        else if (opcion == 5) {
            listarComentariosDesdeFecha();
            system("pause");
        }
    } while (opcion != 0);
}

int main() {
    cargarDatos();

    cout << "===== INICIO DE SESION =====\n";
    int idUsuario = login();

    if (idUsuario == -1) {
        cout << "Usuario invalido\n";
        return 0;
    }

    cout << "Inicio de sesion exitoso.\n";
    menuPrincipal();

    cout << "\nHasta pronto!\n";
    return 0;
}
