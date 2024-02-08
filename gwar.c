#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>

typedef struct tanque {

	int x,y;
	int w,h;
} tanque_t;

typedef struct poder {

	int x,y;
	int w,h;
	int tipo;
} poder_t;

typedef struct bala {

	int x, y; 
	int w,h; 
} bala_t;


typedef struct enemigo {

	int x,y;
	int w,h;
	int clase;
} enemigo_t;

typedef struct bloque {

	int x,y;
	int w,h;
	int tipo;
} bloque_t;

typedef struct bloque2 {

	int x,y;
	int w,h;

} bloque2_t;

//base                      0
//ladrillo ancho vertical   1
//ladrillo delgado vertical 2
//ladrillo horizontal       3
//Hierro ancho vertical     4
//Hierro delgado vertical   5
//hierro horizontal         6
//Arbol                     7
//Arbol2                    8


// Interfaz: Definir areas graficas
static SDL_Surface *pantalla;
static SDL_Surface *titulo;
static SDL_Surface *numero;
static SDL_Surface *end;
static SDL_Surface *base;
static SDL_Surface *arbol;
static SDL_Surface *arbol2;
static SDL_Surface *muro_ladrillo;
static SDL_Surface *muro_ladrillo_delgado;
static SDL_Surface *muro_ladrillo2;
static SDL_Surface *muro_hierro;
static SDL_Surface *muro_hierro_delgado;
static SDL_Surface *muro_hierro2;


// Jugador
static SDL_Surface *Jtanque_arriba;
static SDL_Surface *Jtanque_abajo;
static SDL_Surface *Jtanque_izq;
static SDL_Surface *Jtanque_der;
static SDL_Surface *victoria;
static SDL_Surface *jugador;
static SDL_Surface *base_destruida;
static SDL_Surface *perder;
static SDL_Surface *bandera;
static SDL_Surface *enemigos;

// Poderes
static SDL_Surface *proteccion;
static SDL_Surface *poder_casco;
static SDL_Surface *poder_granada;
static SDL_Surface *poder_pala;
static SDL_Surface *poder_tiempo;

//Enemigos
static SDL_Surface *tanque_basico_arriba;
static SDL_Surface *tanque_basico_abajo;
static SDL_Surface *tanque_basico_izq;
static SDL_Surface *tanque_basico_der;

static SDL_Surface *tanque_basico2_arriba;
static SDL_Surface *tanque_basico2_abajo;
static SDL_Surface *tanque_basico2_izq;
static SDL_Surface *tanque_basico2_der;

static SDL_Surface *tanque_rapido_arriba;
static SDL_Surface *tanque_rapido_abajo;
static SDL_Surface *tanque_rapido_izq;
static SDL_Surface *tanque_rapido_der;

static SDL_Surface *tanque_blindado_arriba_c0;
static SDL_Surface *tanque_blindado_arriba_c1;
static SDL_Surface *tanque_blindado_arriba_c2;
static SDL_Surface *tanque_blindado_arriba_c3;

static SDL_Surface *tanque_blindado_abajo_c0;
static SDL_Surface *tanque_blindado_abajo_c1;
static SDL_Surface *tanque_blindado_abajo_c2;
static SDL_Surface *tanque_blindado_abajo_c3;

static SDL_Surface *tanque_blindado_izq_c0;
static SDL_Surface *tanque_blindado_izq_c1;
static SDL_Surface *tanque_blindado_izq_c2;
static SDL_Surface *tanque_blindado_izq_c3;

static SDL_Surface *tanque_blindado_der_c0;
static SDL_Surface *tanque_blindado_der_c1;
static SDL_Surface *tanque_blindado_der_c2;
static SDL_Surface *tanque_blindado_der_c3;


// Instancia (Elementos)
static tanque_t tanque;
static poder_t poder[3];
static bala_t bala;
static enemigo_t enemigo[4];
static bala_t bala_enemigo[4];
static bloque_t bloque[200];
static bloque2_t bloque2[5];

int dirtiro;
int dirtenemigo1=0;
int dirtenemigo2=0;
int dirtenemigo3=0;
int dirtenemigo4=0;


static void estructura_menu() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = -210;
	src.y = -60;
	src.w = 250;
	src.h = 180;

	SDL_BlitSurface(titulo, NULL, pantalla , &src);

}

//Marco azul de pantalla 

static void marco(){
	int i,b;
	SDL_Rect src;
		//Izq
		bloque2[0].x = 0;
		bloque2[0].y = 0;
		bloque2[0].w = 32;
		bloque2[0].h = 450;

		//Arriba/abajo
	b=0;
	for(i=1; i<3;i++){
		bloque2[i].x = 0;
		bloque2[i].y = 0+b;
		bloque2[i].w = 450;
		bloque2[i].h = 32;
		b+=448;
		}

		//Der
	b=0;
	for(i=3; i<5;i++){
		bloque2[i].x = 450+b;
		bloque2[i].y = 0;
		bloque2[i].w = 64;
		bloque2[i].h = 480;
		b+=32;
	}

		//Forma/Color
	for (i = 0; i < 5; i++) {

		src.x = bloque2[i].x;
		src.y = bloque2[i].y;
		src.w = bloque2[i].w;
		src.h = bloque2[i].h;

		SDL_FillRect(pantalla, &src, 4);

	}

}


static void estructura_fondo(){

//Area Grafica de fondo
	SDL_Rect src;

	src.x = 0;
	src.y = 0;
	src.w = pantalla->w;
	src.h = pantalla->h;


	int r = SDL_FillRect(pantalla, &src, 0);
}

static void estructura_mapa() {

	SDL_Rect src;
	int i;

	for (i = 0; i <= 200; i++) {

		src.x = bloque[i].x;
		src.y = bloque[i].y;
		src.w = bloque[i].w;
		src.h = bloque[i].h;
		
		//Definiendo tipos de estructuras
			//base                      0
			//ladrillo ancho vertical   1
			//ladrillo delgado vertical 2
			//ladrillo horizontal       3
			//Hierro ancho vertical     4
			//Hierro delgado vertical   5
			//hierro horizontal         6
			//Arbol                     7
			//Arbol2                    8

		if(bloque[i].tipo==0){
			SDL_BlitSurface(base, NULL, pantalla ,&src);
			SDL_SetColorKey(base,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(base->format,255,255,255));
		}
		
		if(bloque[i].tipo==1){
			SDL_BlitSurface(muro_ladrillo, NULL, pantalla , &src);
		}

		if(bloque[i].tipo==2){
			SDL_BlitSurface(muro_ladrillo_delgado, NULL, pantalla , &src);
		}
				
		if(bloque[i].tipo==3){
			SDL_BlitSurface(muro_ladrillo2, NULL, pantalla, &src);
		}
		
		if(bloque[i].tipo==4){
			SDL_BlitSurface(muro_hierro, NULL, pantalla, &src);
		}

		if(bloque[i].tipo==5){
			SDL_BlitSurface(muro_hierro_delgado, NULL, pantalla, &src);
		}

		if(bloque[i].tipo==6){
			SDL_BlitSurface(muro_hierro2, NULL, pantalla, &src);
		}
			
		if(bloque[i].tipo==7){
			SDL_BlitSurface(arbol, NULL, pantalla, &src);
		}
		
		if(bloque[i].tipo==8){
			SDL_BlitSurface(arbol2, NULL, pantalla, &src);
		}
	
	
	}
}


int r=0;
static void estructura_perder_ganar() {

	SDL_Rect dest;
	
	if(r==1){
		dest.x = 128;
		dest.y = 144;
		dest.w = 248;
		dest.h = 160;
		SDL_BlitSurface(perder, NULL, pantalla, &dest);
		SDL_SetColorKey(perder,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(perder->format,255,255,255));}
	if(r==2){
		dest.x = -210;
		dest.y = -60;
		dest.w = 250;
		dest.h = 180;
		SDL_BlitSurface(victoria, NULL, pantalla, &dest);
		SDL_SetColorKey(victoria,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(victoria->format,255,255,255));}
}


//Marcadores
int vidas=0;
int marcador_vidas() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 120 - vidas*60; 
	src.y = 0;
	src.w = 65;
	src.h = 65;

	dest.x = 450;
	dest.y = 175;
	dest.w = 65;
	dest.h = 65;


	SDL_BlitSurface(numero, &src, pantalla, &dest);

}

int puntaje;
int marcador_puntaje() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 384;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = 448;
	dest.y = 32;
	dest.w = 64;
	dest.h = 64;

	if (puntaje>0){
	src.x -= 64*puntaje;
	}
	SDL_BlitSurface(numero, &src, pantalla, &dest);
}


static void clean_map(){

	int i;
	for(i=0; i<200; i++){
		bloque[i].x=400;
	}

}


static void base1(){

// Marco de base
	//base                      0
	//ladrillo delgado vertical 2
	//ladrillo horizontal       3
	//derecha
	bloque[0].x = 208;  
	bloque[0].y = 400;
	bloque[0].w = 16;
	bloque[0].h = 32;
	bloque[0].tipo = 1;
	
	//izquirda
	bloque[1].x = 256;
	bloque[1].y = 400;
	bloque[1].w = 16;
	bloque[1].h = 32;
	bloque[1].tipo = 1;

	//arriba
	bloque[2].x = 224;
	bloque[2].y = 400;
	bloque[2].w = 32;
	bloque[2].h = 32;
	bloque[2].tipo = 3;
	
	//emblema
	bloque[3].x = 224;
	bloque[3].y = 416;
	bloque[3].w = 16;
	bloque[3].h = 32;
	bloque[3].tipo = 0;


}


static void in_mapa1(){
	int i,a;

	bloque[4].x = 32;
	bloque[4].y = 240;
	bloque[4].w = 32;
	bloque[4].h = 16;
	bloque[4].tipo = 3;

	bloque[5].x = 32;
	bloque[5].y = 256;
	bloque[5].w = 32;
	bloque[5].h = 16;
	bloque[5].tipo = 6;
	a=0;
	
	bloque[6].x = 416;
	bloque[6].y = 240;
	bloque[6].w = 32;
	bloque[6].h = 16;
	bloque[6].tipo = 3;

	bloque[7].x = 416;
	bloque[7].y = 256;
	bloque[7].w = 32;
	bloque[7].h = 16;
	bloque[7].tipo =6;

for( i = 8; i<17; i++){
	bloque[i].x = 64;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}
	a=0;
for( i =17; i<24; i++){
	bloque[i].x = 64;
	bloque[i].y = 304+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =24; i<33; i++){
	bloque[i].x = 128;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =33; i<40; i++){
	bloque[i].x = 128;
	bloque[i].y = 304+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =42; i<47; i++){
	bloque[i].x = 192;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =47; i<53; i++){
	bloque[i].x = 192;
	bloque[i].y = 272+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =53; i<60; i++){
	bloque[i].x = 256;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =60; i<66; i++){
	bloque[i].x = 256;
	bloque[i].y = 272+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =66; i<75; i++){
	bloque[i].x = 320;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =75; i<82; i++){
	bloque[i].x = 320;
	bloque[i].y = 304+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =82; i<91; i++){
	bloque[i].x = 384;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =91; i<98; i++){
	bloque[i].x = 384;
	bloque[i].y = 304+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

//F
	a=0;
for( i =98; i<100; i++){
	bloque[i].x = 96+a;
	bloque[i].y = 240;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=32;
	}

	a=0;
for( i =100; i<102; i++){
	bloque[i].x = 320+a;
	bloque[i].y = 240;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=32;
	}

	a=0;
for( i =102; i<104; i++){
	bloque[i].x = 96+a;
	bloque[i].y = 256;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=32;
	}

	a=0;
for( i =104; i<106; i++){
	bloque[i].x = 320+a;
	bloque[i].y = 256;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=32;
	}
//Cc i d
	a=0;
for( i =106; i<108; i++){
	bloque[i].x = 192;
	bloque[i].y = 208+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for( i =108; i<110; i++){
	bloque[i].x = 256;
	bloque[i].y = 208+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}
//Cc
	a=0;
for( i =110; i<112; i++){
	bloque[i].x = 224;
	bloque[i].y = 128+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 6;
	a+=16;
	}

	a=0;
for( i =112; i<114; i++){
	bloque[i].x = 224;
	bloque[i].y = 288+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

}



static void in_mapa2() {

	int i,a;

	a=0;
	for(i=4; i<8; i++){

		bloque[i].x = 64;
		bloque[i].y = 64+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}

	a=0;
	for(i=8; i<10; i++){
		bloque[i].x = 64;
		bloque[i].y = 224 + a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}
	
	a=0;
	for(i=10; i<21; i++){

		bloque[i].x = 64;
		bloque[i].y = 288+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}

	a=0;
	for(i=21; i<23; i++){

		bloque[i].x = 96;
		bloque[i].y = 224+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}

	a=0;
	for(i=23; i<27; i++){

		bloque[i].x = 128;
		bloque[i].y = 128+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}


		bloque[27].x = 128;
		bloque[27].y = 224;
		bloque[27].w = 32;
		bloque[27].h = 16;
		bloque[27].tipo = 3;

		bloque[28].x = 128;
		bloque[28].y = 240;
		bloque[28].w = 32;
		bloque[28].h = 16;
		bloque[28].tipo = 3;

	a=0;
	for(i=29; i<33; i++){

		bloque[i].x = 128;
		bloque[i].y = 320+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;

	}

		bloque[33].x = 128;
		bloque[33].y = 416;
		bloque[33].w = 32;
		bloque[33].h = 16;
		bloque[33].tipo = 3;

		bloque[34].x = 128;
		bloque[34].y = 432;
		bloque[34].w = 32;
		bloque[34].h = 16;
		bloque[34].tipo = 3;


		bloque[35].x = 192;
		bloque[35].y = 192;
		bloque[35].w = 32;
		bloque[35].h = 16;
		bloque[35].tipo = 3;

		bloque[36].x = 192;
		bloque[36].y = 208;
		bloque[36].w = 32;
		bloque[36].h = 16;
		bloque[36].tipo = 3;

	a=0;
	for(i=37; i<45; i++){

		bloque[i].x = 192;
		bloque[i].y = 256+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}

		bloque[45].x = 224;
		bloque[45].y = 96;
		bloque[45].w = 32;
		bloque[45].h = 16;
		bloque[45].tipo = 3;

		bloque[46].x = 224;
		bloque[46].y = 112;
		bloque[46].w = 32;
		bloque[46].h = 16;
		bloque[46].tipo = 3;

		bloque[47].x = 224;
		bloque[47].y = 352;
		bloque[47].w = 32;
		bloque[47].h = 16;
		bloque[47].tipo = 3;

		bloque[48].x = 224;
		bloque[48].y = 368;
		bloque[48].w = 32;
		bloque[48].h = 16;
		bloque[48].tipo = 3;

		bloque[49].x = 160;
		bloque[49].y = 240;
		bloque[49].w = 32;
		bloque[49].h = 16;
		bloque[49].tipo = 7;

	a=0;
	for(i=51; i<55; i++){

		bloque[i].x = 256;
		bloque[i].y = 64+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;

	}


	a=0;
	for(i=55; i<63; i++){

		bloque[i].x = 256;
		bloque[i].y = 256+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}

	a=0;
	for(i=63; i<67; i++){

		bloque[i].x = 320;
		bloque[i].y = 64+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;

	}

		bloque[67].x = 320;
		bloque[67].y = 160;
		bloque[67].w = 32;
		bloque[67].h = 16;
		bloque[67].tipo = 3;

		bloque[68].x = 320;
		bloque[68].y = 176;
		bloque[68].w = 32;
		bloque[68].h = 16;
		bloque[68].tipo = 3;

		bloque[69].x = 320;
		bloque[69].y = 256;
		bloque[69].w = 32;
		bloque[69].h = 16;
		bloque[69].tipo = 3;

		bloque[70].x = 320;
		bloque[70].y = 272;
		bloque[70].w = 32;
		bloque[70].h = 16;
		bloque[70].tipo = 3;

		bloque[71].x = 320;
		bloque[71].y = 320;
		bloque[71].w = 32;
		bloque[71].h = 16;
		bloque[71].tipo = 3;

		bloque[72].x = 320;
		bloque[72].y = 336;
		bloque[72].w = 32;
		bloque[72].h = 16;
		bloque[72].tipo = 3;


	a=0;
	for(i=73; i<77; i++){

		bloque[i].x = 320;
		bloque[i].y = 384+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;
	}

		bloque[77].x = 352;
		bloque[77].y = 416;
		bloque[77].w = 32;
		bloque[77].h = 16;
		bloque[77].tipo = 3;

		bloque[78].x = 352;
		bloque[78].y = 432;
		bloque[78].w = 32;
		bloque[78].h = 16;
		bloque[78].tipo = 3;

	a=0;
	for(i=79; i<83; i++){

		bloque[i].x = 384;
		bloque[i].y = 64+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;

	}

		bloque[83].x = 384;
		bloque[83].y = 160;
		bloque[83].w = 32;
		bloque[83].h = 16;
		bloque[83].tipo = 3;

		bloque[84].x = 384;
		bloque[84].y = 176;
		bloque[84].w = 32;
		bloque[84].h = 16;
		bloque[84].tipo = 3;

	a=0;
	for(i=85; i<93; i++){

		bloque[i].x = 384;
		bloque[i].y = 224+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;

	}

	a=0;
	for(i=93; i<97; i++){

		bloque[i].x = 384;
		bloque[i].y = 384+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 3;
		a+=16;

	}

		bloque[97].x = 224;
		bloque[97].y = 320;
		bloque[97].w = 16;
		bloque[97].h = 32;
		bloque[97].tipo = 3;

		bloque[98].x = 224;
		bloque[98].y = 336;
		bloque[98].w = 16;
		bloque[98].h = 32;
		bloque[98].tipo = 3;

		bloque[99].x = 32;
		bloque[99].y = 288;
		bloque[99].w = 32;
		bloque[99].h = 16;
		bloque[99].tipo = 6;

		bloque[100].x = 32;
		bloque[100].y = 304;
		bloque[100].w = 32;
		bloque[100].h = 16;
		bloque[100].tipo = 6;


	a=0;
	for(i=101; i<105; i++){

		bloque[i].x = 128;
		bloque[i].y = 32+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}


	a=0;
	for(i=105; i<109; i++){

		bloque[i].x = 128;
		bloque[i].y = 256+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}

	a=0;
	for(i=109; i<111; i++){

		bloque[i].x = 224;
		bloque[i].y = 160+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}


	a=0;
	for(i=111; i<113; i++){

		bloque[i].x = 256;
		bloque[i].y = 32+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}

	a=0;
	for(i=113; i<115; i++){

		bloque[i].x = 256;
		bloque[i].y = 224+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;
	}


	a=0;
	for(i=115; i<117; i++){

		bloque[i].x = 288;
		bloque[i].y = 192+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}

	a=0;
	for(i=117; i<119; i++){

		bloque[i].x = 320;
		bloque[i].y = 128+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}

	a=0;
	for(i=119; i<121; i++){

		bloque[i].x = 352;
		bloque[i].y = 96+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}

	a=0;
	for(i=121; i<123; i++){

		bloque[i].x = 352;
		bloque[i].y = 320+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}


	a=0;
	for(i=123; i<125; i++){

		bloque[i].x = 416;
		bloque[i].y = 160+a;
		bloque[i].w = 32;
		bloque[i].h = 16;
		bloque[i].tipo = 6;
		a+=16;

	}
	
		bloque[125].x = 32;
		bloque[125].y = 160;
		bloque[125].w = 32;
		bloque[125].h = 32;
		bloque[125].tipo = 7;

	a=0;
	for( i=126; i<128 ; i++) {
		bloque[i].x = 32 + a;
		bloque[i].y = 192;
		bloque[i].w = 32;
		bloque[i].h = 32;
		bloque[i].tipo = 7;
		a+= 32;
	}

	a=0;
	for( i=128; i<131 ; i++) {
		bloque[i].x = 160 +a;
		bloque[i].y = 224;
		bloque[i].w = 32;
		bloque[i].h = 32;
		bloque[i].tipo = 7;
		a+=32;
	}
	
	
		bloque[131].x = 160;
		bloque[131].y = 256;
		bloque[131].w = 32;
		bloque[131].h = 32;
		bloque[131].tipo = 7;


	a=0;
	for( i=132; i<135 ; i++) {
		bloque[i].x = 352;
		bloque[i].y = 160 + a;
		bloque[i].w = 32;
		bloque[i].h = 32;
		bloque[i].tipo = 7;
		a+=32;
	}

}



static void in_mapa3() {

	int i,a;

		a=0;
	for(i=4; i<6; i++){

	bloque[i].x = 32;
	bloque[i].y = 96+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	bloque[6].x = 32;
	bloque[6].y = 288;
	bloque[6].w = 32;
	bloque[6].h = 16;
	bloque[6].tipo = 3;

	bloque[7].x = 32;
	bloque[7].y = 304;
	bloque[7].w = 32;
	bloque[7].h = 16;
	bloque[7].tipo = 3;


	a=0;
for(i=8; i<12; i++){
	bloque[i].x = 32;
	bloque[i].y = 352+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	bloque[12].x = 64;
	bloque[12].y = 272;
	bloque[12].w = 32;
	bloque[12].h = 16;
	bloque[12].tipo = 3;


	a=0;
for(i=13; i<17; i++){
	bloque[i].x = 64;
	bloque[i].y = 384+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=17; i<19; i++){
	bloque[i].x = 96;
	bloque[i].y = 416+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=19; i<21; i++){
	bloque[i].x = 112;
	bloque[i].y = 288+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	bloque[21].x = 128;
	bloque[21].y = 272;
	bloque[21].w = 32;
	bloque[21].h = 16;
	bloque[21].tipo = 3;


	a=0;
for(i=22; i<24; i++){
	bloque[i].x = 144;
	bloque[i].y = 288+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=24; i<28; i++){
	bloque[i].x = 160;
	bloque[i].y = 32+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for(i=28; i<30; i++){
	bloque[i].x = 160;
	bloque[i].y = 160+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=30; i<32; i++){
	bloque[i].x = 192;
	bloque[i].y = 160+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}
	
	a=0;
for(i=32; i<34; i++){
	bloque[i].x = 192;
	bloque[i].y = 320+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for(i=34; i<38; i++){
	bloque[i].x = 224;
	bloque[i].y = 160+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	bloque[38].x = 224;
	bloque[38].y = 288;
	bloque[38].w = 32;
	bloque[38].h = 16;
	bloque[38].tipo = 3;

	a=0;
for(i=39; i<42; i++){
	bloque[i].x = 256;
	bloque[i].y = 128+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	bloque[42].x = 256;
	bloque[42].y = 288;
	bloque[42].w = 32;
	bloque[42].h = 16;
	bloque[42].tipo = 3;

	a=0;
for(i=43; i<45; i++){
	bloque[i].x = 256;
	bloque[i].y = 336+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=45; i<47; i++){
	bloque[i].x = 288;
	bloque[i].y = 32+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	bloque[47].x = 288;
	bloque[47].y = 288;
	bloque[47].w = 32;
	bloque[47].h = 16;
	bloque[47].tipo = 3;

	a=0;
for(i=48; i<50; i++){
	bloque[i].x = 288;
	bloque[i].y = 336+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=50; i<54; i++){
	bloque[i].x = 320;
	bloque[i].y = 128+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}	

	a=0;
for(i=54; i<56; i++){
	bloque[i].x = 320;
	bloque[i].y = 416+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	a=0;
for(i=56; i<58; i++){
	bloque[i].x = 352;
	bloque[i].y = 128+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}

	a=0;
for(i=58; i<60; i++){
	bloque[i].x = 384;
	bloque[i].y = 128+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 3;
	a+=16;
	}


	bloque[60].x = 208;
	bloque[60].y = 400;
	bloque[60].w = 32;
	bloque[60].h = 16;
	bloque[60].tipo = 3;


	bloque[61].x = 240;
	bloque[61].y = 400;
	bloque[61].w = 32;
	bloque[61].h = 16;
	bloque[61].tipo = 3;




	bloque[62].x = 64;
	bloque[62].y = 288;
	bloque[62].w = 16;
	bloque[62].h = 32;
	bloque[62].tipo = 1;

	bloque[63].x = 208;
	bloque[63].y = 288;
	bloque[63].w = 16;
	bloque[63].h = 32;
	bloque[63].tipo = 1;

	bloque[64].x = 256;
	bloque[64].y = 416;
	bloque[64].w = 16;
	bloque[64].h = 32;
	bloque[64].tipo = 1;

	bloque[65].x = 208;
	bloque[65].y = 416;
	bloque[65].w = 16;
	bloque[65].h = 32;
	bloque[65].tipo = 1;

	bloque[66].x = 400;
	bloque[66].y = 160;
	bloque[66].w = 16;
	bloque[66].h = 32;
	bloque[66].tipo = 1;

	bloque[67].x = 400;
	bloque[67].y = 192;
	bloque[67].w = 16;
	bloque[67].h = 32;
	bloque[67].tipo = 1;

	bloque[68].x = 416;
	bloque[68].y = 128;
	bloque[68].w = 16;
	bloque[68].h = 32;
	bloque[68].tipo = 1;


	a=0;
for(i=69; i<71; i++){
	bloque[i].x = 32;
	bloque[i].y = 416+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 6;
	a+=16;
	}


	a=0;
for(i=71; i<73; i++){
	bloque[i].x = 224;
	bloque[i].y = 224+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 6;
	a+=16;}


	a=0;
for(i=73; i<75; i++){
	bloque[i].x = 256;
	bloque[i].y = 224+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 6;
	a+=16;
	}	


	a=0;
for(i=75; i<77; i++){
	bloque[i].x = 288;
	bloque[i].y = 224+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 6;
	a+=16;
	}	


	a=0;
for(i=77; i<80; i++){
	bloque[i].x = 352+a;
	bloque[i].y = 80;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 6;
	a+=32;
	}	


	bloque[80].x = 128;
	bloque[80].y = 352;
	bloque[80].w = 16;
	bloque[80].h = 32;
	bloque[80].tipo = 4;

	bloque[81].x = 128;
	bloque[81].y = 384;
	bloque[81].w = 16;
	bloque[81].h = 32;
	bloque[81].tipo = 4;

	a=0;
for(i=82; i<85; i++){
	bloque[i].x = 32;
	bloque[i].y = 128+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=16;
	}	


	a=0;
for(i=85; i<90; i++){
	bloque[i].x = 64;
	bloque[i].y = 66+a;
	bloque[i].w = 32;
	bloque[i].h = 32;
	bloque[i].tipo = 7;
	a+=32;
	}	


	a=0;
for(i=90; i<95; i++){
	bloque[i].x = 96;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 32;
	bloque[i].tipo = 7;
	a+=32;
	}


	a=0;
for(i=95; i<100; i++){
	bloque[i].x = 128;
	bloque[i].y = 64+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	



	a=0;
for(i=100; i<105; i++){
	bloque[i].x = 320;
	bloque[i].y = 256+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	


	a=0;
for(i=105; i<110; i++){
	bloque[i].x = 352;
	bloque[i].y = 256+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}


	a=0;
for(i=110; i<116; i++){
	bloque[i].x = 384;
	bloque[i].y = 224+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	

	a=0;
for(i=116; i<119; i++){
	bloque[i].x = 416;
	bloque[i].y = 256+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	


	a=0;
for(i=121; i<123; i++){
	bloque[i].x = 32;
	bloque[i].y = 176+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=16;
	}	
	bloque[123].x = 32;
	bloque[123].y = 176+a;
	bloque[123].w = 32;
	bloque[123].h = 16;
	bloque[123].tipo = 8;
	

	a=0;
for(i=124; i<129; i++){
	bloque[i].x = 64;
	bloque[i].y = 80+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	
	bloque[129].x = 64;
	bloque[129].y = 80+a;
	bloque[129].w = 32;
	bloque[129].h = 16;
	bloque[129].tipo = 8;

	a=0;
for(i=130; i<134; i++){
	bloque[i].x = 96;
	bloque[i].y = 80+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	
	bloque[134].x = 96;
	bloque[134].y = 80+a;
	bloque[134].w = 32;
	bloque[134].h = 16;
	bloque[134].tipo = 8;

	a=0;
for(i=135; i<139; i++){
	bloque[i].x = 128;
	bloque[i].y = 80+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}	
	bloque[139].x = 128;
	bloque[139].y = 80+a;
	bloque[139].w = 32;
	bloque[139].h = 16;
	bloque[139].tipo = 8;

	a=0;
for(i=140; i<145; i++){
	bloque[i].x = 320;
	bloque[i].y = 272+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}

	a=0;
for(i=145; i<150; i++){
	bloque[i].x = 352;
	bloque[i].y = 272+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}

	a=0;
for(i=150; i<156; i++){
	bloque[i].x = 384;
	bloque[i].y = 240+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}

	a=0;
for(i=156; i<159; i++){
	bloque[i].x = 416;
	bloque[i].y = 272+a;
	bloque[i].w = 32;
	bloque[i].h = 16;
	bloque[i].tipo = 7;
	a+=32;
	}

}



int mapa=1;
static void in_tanque() {

	tanque.x = 176;
	tanque.y = 418;
	tanque.w = 26;
	tanque.h = 25;
	
	if(mapa==1){
	enemigo[0].x=34;
	enemigo[0].y=34;
	enemigo[0].w=25;
	enemigo[0].h=25;
	enemigo[0].clase=0;
	}
	
	enemigo[1].x=227;
	enemigo[1].y=34;
	enemigo[1].w=25;
	enemigo[1].h=25;
	enemigo[1].clase=1;

	enemigo[2].x=418;
	enemigo[2].y=34;
	enemigo[2].w=25;
	enemigo[2].h=25;
	
	
	if(mapa==2 || mapa==3){
	enemigo[3].x=33;
	enemigo[3].y=33;
	enemigo[3].w=25;
	enemigo[3].h=25;
	enemigo[3].clase=3;
	}

}


static void estructura_tanquearriba() {
	SDL_Rect src;
		src.x = tanque.x;
		src.y = tanque.y;
		src.w = tanque.w;
		src.h = tanque.h;
		SDL_BlitSurface(Jtanque_arriba, NULL, pantalla,&src);
		SDL_SetColorKey(Jtanque_arriba,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(Jtanque_arriba->format,255,255,255));
}
static void estructura_tanqueabajo() {
	SDL_Rect src;
		src.x = tanque.x;
		src.y = tanque.y;
		src.w = tanque.w;
		src.h = tanque.h;
		SDL_BlitSurface(Jtanque_abajo, NULL, pantalla,&src);
		SDL_SetColorKey(Jtanque_abajo,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(Jtanque_arriba->format,255,255,255));
}
static void estructura_tanqueizq() {
	SDL_Rect src;
		src.x = tanque.x;
		src.y = tanque.y;
		src.w = tanque.w;
		src.h = tanque.h;
		SDL_BlitSurface(Jtanque_izq, NULL, pantalla,&src);
		SDL_SetColorKey(Jtanque_izq,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(Jtanque_arriba->format,255,255,255));
}
static void estructura_tanqueder() {
	SDL_Rect src;
		src.x = tanque.x;
		src.y = tanque.y;
		src.w = tanque.w;
		src.h = tanque.h;
		SDL_BlitSurface(Jtanque_der, NULL, pantalla,&src);
		SDL_SetColorKey(Jtanque_der,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(Jtanque_arriba->format,255,255,255));
}



static void in_bala() {

	bala.x = -10;
	bala.y = -10;
	bala.w = 5;
	bala.h = 5;	
}

static void in_bala1() {

	bala_enemigo[0].x = -10;
	bala_enemigo[0].y = -10;
	bala_enemigo[0].w = 5;
	bala_enemigo[0].h = 5;
	
}

static void in_bala2() {

	bala_enemigo[1].x = -10;
	bala_enemigo[1].y = -10;
	bala_enemigo[1].w = 5;
	bala_enemigo[1].h = 5;
	
}

static void in_bala3() {

	bala_enemigo[2].x = -10;
	bala_enemigo[2].y = -10;
	bala_enemigo[2].w = 5;
	bala_enemigo[2].h = 5;
	
}

static void in_bala4() {

	bala_enemigo[3].x = -10;
	bala_enemigo[3].y = -10;
	bala_enemigo[3].w = 5;
	bala_enemigo[3].h = 5;
	
}


int colision(bloque_t a, tanque_t b) {

	int arriba_a, arriba_b;
	int abajo_a, abajo_b;
	int izq_a, izq_b;
	int der_a, der_b;
	

		izq_a = a.x;
		der_a = a.x + a.w;
		arriba_a = a.y;
		abajo_a = a.y + a.h;

		izq_b = b.x;
		der_b = b.x + b.w;
		arriba_b = b.y;
		abajo_b = b.y + b.h;


	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}
	if (a.tipo==7 || a.tipo==8){
		return 0;
	}


	return 1;
}



int dist_proteccion=0;
int colision_tanque_enemigo(enemigo_t b, tanque_t a) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

		izq_a = a.x;
		der_a = a.x + a.w;
		arriba_a = a.y;
		abajo_a = a.y + a.h;

		izq_b = b.x;
		der_b = b.x + b.w;
		arriba_b = b.y;
		abajo_b = b.y + b.h;
	

	if(dist_proteccion<=201){
		return 0;
	}

	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	return 1;


}



static void tanque_enemigo(){
	int i,hit,x;
	if(mapa==1){x=0;}
	if(mapa!=1){x=1;}
	for(i=0+x; i<4; i++){
		hit=colision_tanque_enemigo(enemigo[i],tanque);
		if(hit==1){
		vidas+=1;
		tanque.x = 170;
		tanque.y = 418;
		dist_proteccion=0;
		
		}	
	}	
}



int colision_enemigo_mapa(bloque_t a, enemigo_t b) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

		izq_a = a.x;
		der_a = a.x + a.w;
		arriba_a = a.y;
		abajo_a = a.y + a.h;

		izq_b = b.x;
		der_b = b.x + b.w;
		arriba_b = b.y;
		abajo_b = b.y + b.h;


	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	return 1;


}


int colision_bala(bloque_t a, bala_t b) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izq_a = a.x;
	der_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izq_b = b.x;
	der_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;

	if(a.tipo==7 || a.tipo==8){
		return 0;
	}



	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	return 1;


}


int colision_bala_enemigo(bala_t a, enemigo_t b) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izq_a = a.x;
	der_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izq_b = b.x;
	der_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;

	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	return 1;


}


int tiro1=0;
int tiro2=0;
int tiro3=0;
int tiro4=0;
	int dir1=1;
	int dir2=1;
	int dir3=1;
	int dir4=1;
		int dirtiro1;
		int dirtiro2;
		int dirtiro3;
		int dirtiro4;



static void pos_in_bala_enemigo( int x ){
	int a;
	if(x==0){a=dir1;}	
	if(x==1){a=dir2;}	
	if(x==2){a=dir3;}	
	if(x==3){a=dir4;}	
	
	if(a==0){

		bala_enemigo[x].x = enemigo[x].x+10;
		bala_enemigo[x].y = enemigo[x].y-10;

	}

	if(a==1){

		bala_enemigo[x].x = enemigo[x].x+10;
		bala_enemigo[x].y = enemigo[x].y+ enemigo[x].h;

		if(x==0){dirtiro1=1;}	
		if(x==1){dirtiro2=1;}	
		if(x==2){dirtiro3=1;}	
		if(x==3){dirtiro4=1;}	
	}

	if(a==2){

		bala_enemigo[x].x = enemigo[x].x + enemigo[x].w;
		bala_enemigo[x].y = enemigo[x].y+10;

		if(x==0){dirtiro1=2;}	
		if(x==1){dirtiro2=2;}	
		if(x==2){dirtiro3=2;}	
		if(x==3){dirtiro4=2;}	
	}

	if(a==3){

		bala_enemigo[x].x = enemigo[x].x -10;
		bala_enemigo[x].y = enemigo[x].y+10;

		if(x==0){dirtiro1=3;}	
		if(x==1){dirtiro2=3;}	
		if(x==2){dirtiro3=3;}	
		if(x==3){dirtiro4=3;}	
	}	

}

		
static void pos_in_tanque( int dir){
	if(dir==0){

	bala.x = tanque.x+10;
	bala.y = tanque.y-10;
	dirtiro=0;

	}

	if(dir==1){
	bala.x = tanque.x+10;
	bala.y = tanque.y+ tanque.h;
	dirtiro=1;
	}

	if(dir==2){
	bala.x = tanque.x + tanque.w;
	bala.y = tanque.y + 10;
	dirtiro=2;
	}

	if(dir==3){

	bala.x = tanque.x -10;
	bala.y = tanque.y+10;
	dirtiro=3;

	}



}



int dist_p=450;
int dist_Jtiempo=200;

static void mover_tanque(int d) {
	int i;
	int tanquex=tanque.x;
	int tanquey=tanque.y;
	int r=0;


	if (d == 0) {

		if(tanque.y <= 32) {
			tanque.y = 32;
			}
			else {
			tanque.y -= 3;
			dist_p+=1;
			dist_Jtiempo+=1;
			dist_proteccion+=1;
			}
	}
	
	if (d == 1) {

		if(tanque.y >= pantalla->h - tanque.h-32) {

			tanque.y = pantalla->h - tanque.h-32;

		} else {

			tanque.y += 3;
			dist_p+=1;
			dist_Jtiempo+=1;
			dist_proteccion+=1;
		}
	}


	if (d == 2) {

		if(tanque.x >= pantalla->w - tanque.w -64) {

			tanque.x = pantalla->w - tanque.w-64;

		} else {

			tanque.x += 3;
			dist_p+=1;
			dist_Jtiempo+=1;
			dist_proteccion+=1;
		}
	}
	if (d == 3) {

		if(tanque.x <= 32) {
			tanque.x = 32;
			}
			else {
			tanque.x -= 3;
			dist_p+=1;
			dist_Jtiempo+=1;
			dist_proteccion+=1;
			}
	}



	for(i=0; i<200; i++){

		r= colision(bloque[i], tanque);

		if(r==1){

		break;

		}
	}
	if (r==1){
	tanque.x=tanquex;
	tanque.y=tanquey;
	}
}

static void tiro_enemigo_map( int num) {
	int hit=0;
	int i;
	int a;
	int f;
	int y=0;
	
	if(num==0){
		a=dir1; 
		f=dirtiro1;
	}	
	
	if(num==1){
		a=dir2; 
		f=dirtiro2;
	}	
	
	if(num==2){
		a=dir3; 
		f=dirtiro3;
	}	
	
	if(num==3){
		a=dir4; 
		f=dirtiro4;
	}



	for(i=0; i<200; i++){

		hit= colision_bala(bloque[i], bala_enemigo[num]);
						
		if(hit==1 && bloque[i].tipo==0){
		y=1;
		r=1;
		}
		if(hit==1 && bloque[i].tipo!=7 && bloque[i].tipo!=8){
			
			if(num==0){in_bala1();}	
			if(num==1){in_bala2();}	
			if(num==2){in_bala3();}	
			if(num==3){in_bala4();}

		if(bloque[i].tipo==4 || bloque[i].tipo==5 || bloque[i].tipo==6){y=1;}
		break;

		}

	}


	if (bala_enemigo[num].x < 32 || bala_enemigo[num].x > 440) {
			if(num==0){in_bala1();}	
			if(num==1){in_bala2();}	
			if(num==2){in_bala3();}	
			if(num==3){in_bala4();}
				if(num==0){tiro1=0;}	
				if(num==1){tiro2=0;}	
				if(num==2){tiro3=0;}	
				if(num==3){tiro4=0;}		



	}

	if (bala_enemigo[num].y < 32 || bala_enemigo[num].y >440 ) {
			if(num==0){in_bala1();}	
			if(num==1){in_bala2();}	
			if(num==2){in_bala3();}	
			if(num==3){in_bala4();}
				if(num==0){tiro1=0;}	
				if(num==1){tiro2=0;}	
				if(num==2){tiro3=0;}	
				if(num==3){tiro4=0;}
	}

//S
	if (f==0 &&hit ==0){
	bala_enemigo[num].y -=5;

	}

	if (f==1 &&hit ==0){
	bala_enemigo[num].y +=5;

	}

	if (f==3 &&hit ==0){
	bala_enemigo[num].x -=5;

	}

	if (f==2 &&hit ==0){
	bala_enemigo[num].x +=5;

	}

	if(hit==1 ){
		if(y==0){
		bloque[i].x=1000;
		bloque[i].y=1000;
			if(num==0){tiro1=0;}	
			if(num==1){tiro2=0;}	
			if(num==2){tiro3=0;}	
			if(num==3){tiro4=0;}
		}
	}


}



static void estructura_bala() {

	SDL_Rect src;

	src.x = bala.x;
	src.y = bala.y;
	src.w = bala.w;
	src.h = bala.h;

	SDL_FillRect(pantalla,&src,255);
	
	src.x = bala_enemigo[0].x;
	src.y = bala_enemigo[0].y;
	src.w = bala_enemigo[0].w;
	src.h = bala_enemigo[0].h;

	SDL_FillRect(pantalla,&src,255);

	
	src.x = bala_enemigo[1].x;
	src.y = bala_enemigo[1].y;
	src.w = bala_enemigo[1].w;
	src.h = bala_enemigo[1].h;

	SDL_FillRect(pantalla,&src,255);

	src.x = bala_enemigo[2].x;
	src.y = bala_enemigo[2].y;
	src.w = bala_enemigo[2].w;
	src.h = bala_enemigo[2].h;

	SDL_FillRect(pantalla,&src,255);

	src.x = bala_enemigo[3].x;
	src.y = bala_enemigo[3].y;
	src.w = bala_enemigo[3].w;
	src.h = bala_enemigo[3].h;

	SDL_FillRect(pantalla,&src,255);

}

int tiro=0;

static void disparo(int dirtiro) {
	int hit=0;
	int i;
	int a=0;
	int y=0;

	for(i=0; i<200; i++){

		hit= colision_bala(bloque[i], bala);
		if (hit==1){
                tiro=0;
		}
		if(hit==1 && bloque[i].tipo==0){
		y=1;
		SDL_Rect src;
		src.x = bloque[i].x;
		src.y = bloque[i].y;
		src.w = bloque[i].w;
		src.h = bloque[i].h;
		SDL_BlitSurface(base_destruida, NULL, pantalla,&src);
		SDL_SetColorKey(base_destruida,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(base_destruida->format,255,255,255));
		r=1;
		}
//!=A
		if(hit==1 && bloque[i].tipo!=7 && bloque[i].tipo!=8){
		a=i;
		in_bala();
		if(bloque[i].tipo==4 || bloque[i].tipo==5 || bloque[i].tipo==6){y=1;}
		break;

		}
	}


	if (bala.x < 32 || bala.x > 440) {
		in_bala();
		tiro=0;
	}
	if (bala.y < 32 || bala.y >440) {
		in_bala();
		tiro=0;
	}


	if (dirtiro==0 &&hit ==0){
		bala.y -=5;
	}

	if (dirtiro==1 &&hit ==0){
		bala.y +=5;
	}
	if (dirtiro==3 &&hit ==0){
		bala.x -=5;
	}
	if (dirtiro==2 &&hit ==0){
		bala.x +=5;
	}

	if(hit==1 ){
		if(y==0){
			bloque[a].x=600;
			bloque[a].y=600;
		}
	}
}



int balahit=0;
static void balahit1() {
	int hit=0;
	hit= colision_bala_enemigo(bala, enemigo[0]);
	if(hit==1){
	enemigo[0].x=33;
	enemigo[0].y=33;
	puntaje+=1;
	balahit=1;
	}
}

static void balahit2() {
	int hit=0;
	hit= colision_bala_enemigo(bala, enemigo[1]);
	if(hit==1){
	enemigo[1].x=224;
	enemigo[1].y=32;
	puntaje+=1;
	balahit=1;
	}
}

int c=0;
static void balahit3() {
	int hit=0;

	hit= colision_bala_enemigo(bala, enemigo[2]);
	if(hit==1){
		if(c==0){
		c+=1;
		balahit=1;

		}
		else{
		enemigo[2].x=418;
		enemigo[2].y=34;
		puntaje+=1;
		balahit=1;
		c=0;}
	}
	
}



int h=0;
static void balahit4() {
	int hit=0;

	hit= colision_bala_enemigo(bala, enemigo[3]);
	if(hit==1){
		if(h<3){
		h+=1;
		balahit=1;

		}
		else{
		enemigo[3].x=34;
		enemigo[3].y=34;
		puntaje+=1;
		balahit=1;
		h=0;}
	}
	
}

//Bala enemigo golpee al jugador
int colision_bala_tanque(bala_t a, tanque_t b) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izq_a = a.x;
	der_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izq_b = b.x;
	der_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;
	
	if(dist_proteccion<=201){
		return 0;
	}

	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}


	return 1;
}


// Reaparecer vida-1
static void bala_hit_tanque(int numero){
	int hit;
	
	hit=colision_bala_tanque(bala_enemigo[numero], tanque);

	if(hit==1){
	vidas+=1;
	tanque.x= 176;
	tanque.y= 416;
	dist_proteccion=0;

	}
}


int colision_enemigos(enemigo_t a, enemigo_t b) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izq_a = a.x;
	der_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izq_b = b.x;
	der_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;


	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}
	
	return 1;
}


static void estructura_enemigo_arriba(int enemigos) {
	SDL_Rect src;

		src.x = enemigo[enemigos].x;
		src.y = enemigo[enemigos].y;
		src.w = enemigo[enemigos].w;
		src.h = enemigo[enemigos].h;

		if(enemigo[enemigos].clase==0){
		SDL_BlitSurface(tanque_basico_arriba, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico_arriba,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico_arriba->format,0,0,0));
		}
		if(enemigo[enemigos].clase==1){
		SDL_BlitSurface(tanque_rapido_arriba, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_rapido_arriba,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_rapido_arriba->format,0,0,0));
		}
		if(enemigo[enemigos].clase==2){
		SDL_BlitSurface(tanque_basico2_arriba, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico2_arriba,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico2_arriba->format,0,0,0));
		}

		if(enemigo[enemigos].clase==3){
		
			if(h==0){		
			SDL_BlitSurface(tanque_blindado_arriba_c0, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_arriba_c0,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_arriba_c0->format,0,0,0));
			}
			if(h==1){		
			SDL_BlitSurface(tanque_blindado_arriba_c1, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_arriba_c1,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_arriba_c1->format,0,0,0));
			}
			if(h==2){		
			SDL_BlitSurface(tanque_blindado_arriba_c2, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_arriba_c2,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_arriba_c2->format,255,255,255));
			}
			if(h==3){		
			SDL_BlitSurface(tanque_blindado_arriba_c3, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_arriba_c3,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_arriba_c3->format,255,255,255));
			}
		

		}
}

static void estructura_enemigo_abajo(int enemigos) {
	SDL_Rect src;

		src.x = enemigo[enemigos].x;
		src.y = enemigo[enemigos].y;
		src.w = enemigo[enemigos].w;
		src.h = enemigo[enemigos].h;

		if(enemigo[enemigos].clase==0){
		SDL_BlitSurface(tanque_basico_abajo, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico_abajo,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico_abajo->format,0,0,0));
		}
		if(enemigo[enemigos].clase==1){
		SDL_BlitSurface(tanque_rapido_abajo, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_rapido_abajo,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_rapido_abajo->format,0,0,0));
		}
		if(enemigo[enemigos].clase==2){
		SDL_BlitSurface(tanque_basico2_abajo, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico2_abajo,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico2_abajo->format,0,0,0));
		}
		if(enemigo[enemigos].clase==3){
		
			if(h==0){		
			SDL_BlitSurface(tanque_blindado_abajo_c0, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_abajo_c0,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_abajo_c0->format,0,0,0));
			}
			if(h==1){		
			SDL_BlitSurface(tanque_blindado_abajo_c1, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_abajo_c1,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_abajo_c1->format,0,0,0));
			}
			if(h==2){		
			SDL_BlitSurface(tanque_blindado_abajo_c2, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_abajo_c2,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_abajo_c2->format,255,255,255));
			}
			if(h==3){		
			SDL_BlitSurface(tanque_blindado_abajo_c3, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_abajo_c3,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_abajo_c3->format,255,255,255));
			}
		

		}
}

static void estructura_enemigo_izq(int enemigos) {
	SDL_Rect src;

		src.x = enemigo[enemigos].x;
		src.y = enemigo[enemigos].y;
		src.w = enemigo[enemigos].w;
		src.h = enemigo[enemigos].h;

		if(enemigo[enemigos].clase==0){
		SDL_BlitSurface(tanque_basico_izq, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico_izq,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico_izq->format,0,0,0));
		}
		if(enemigo[enemigos].clase==1){
		SDL_BlitSurface(tanque_rapido_izq, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_rapido_izq,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_rapido_izq->format,0,0,0));
		}
		if(enemigo[enemigos].clase==2){
		SDL_BlitSurface(tanque_basico2_izq, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico2_izq,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico2_izq->format,0,0,0));
		}
		if(enemigo[enemigos].clase==3){
		
			if(h==0){		
			SDL_BlitSurface(tanque_blindado_izq_c0, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_izq_c0,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_izq_c0->format,0,0,0));
			}
			if(h==1){		
			SDL_BlitSurface(tanque_blindado_izq_c1, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_izq_c1,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_izq_c1->format,0,0,0));
			}
			if(h==2){		
			SDL_BlitSurface(tanque_blindado_izq_c2, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_izq_c2,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_izq_c2->format,255,255,255));
			}
			if(h==3){		
			SDL_BlitSurface(tanque_blindado_izq_c3, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_izq_c3,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_izq_c3->format,255,255,255));
			}
		

		}
}

static void estructura_enemigo_der(int enemigos) {
	SDL_Rect src;

		src.x = enemigo[enemigos].x;
		src.y = enemigo[enemigos].y;
		src.w = enemigo[enemigos].w;
		src.h = enemigo[enemigos].h;

		if(enemigo[enemigos].clase==0){
		SDL_BlitSurface(tanque_basico_der, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico_der,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico_der->format,0,0,0));
		}
		if(enemigo[enemigos].clase==1){
		SDL_BlitSurface(tanque_rapido_der, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_rapido_der,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_rapido_der->format,0,0,0));
		}
		if(enemigo[enemigos].clase==2){
		SDL_BlitSurface(tanque_basico2_der, NULL, pantalla,&src);
		SDL_SetColorKey(tanque_basico2_der,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_basico2_der->format,0,0,0));
		}
		if(enemigo[enemigos].clase==3){
		
			if(h==0){		
			SDL_BlitSurface(tanque_blindado_der_c0, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_der_c0,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_der_c0->format,0,0,0));
			}
			if(h==1){		
			SDL_BlitSurface(tanque_blindado_der_c1, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_der_c1,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_der_c1->format,0,0,0));
			}
			if(h==2){		
			SDL_BlitSurface(tanque_blindado_der_c2, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_der_c2,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_der_c2->format,255,255,255));
			}
			if(h==3){		
			SDL_BlitSurface(tanque_blindado_der_c3, NULL, pantalla,&src);
			SDL_SetColorKey(tanque_blindado_der_c3,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(tanque_blindado_der_c3->format,255,255,255));
			}
		

		}
}



static void mover_enemigo1(){

	int enem_x=enemigo[0].x;
 	int enem_y=enemigo[0].y;
	int hit=0;

	if (dir1==0){
		enemigo[0].y-=1;
		dirtenemigo1+=1;

	}


	if (dir1==1){
		enemigo[0].y+=1;
		dirtenemigo1+=1;
	}



	if (dir1==2){
		enemigo[0].x+=1;
		dirtenemigo1+=1;

	}

	if (dir1==3){
		enemigo[0].x-=1;
		dirtenemigo1+=1;

	}
	if(32 >= enemigo[0].x   || enemigo[0].x +25 >= 440){
	enemigo[0].x=enem_x;
 	enemigo[0].y=enem_y;

	srand (time(NULL));
	dir1= rand()%4;
	}
	if ( 32 >= enemigo[0].y   || enemigo[0].y + 26>=440){

	enemigo[0].x=enem_x;
 	enemigo[0].y=enem_y;
	srand (time(NULL));
	dir1= rand()%4;
	}

	int i=0;
	for(i=0; i<200; i++){
		hit= colision_enemigo_mapa(bloque[i], enemigo[0]);

		if (hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8 ){
		break;
		}
	}
	int t;
	int hitt=0;
	for(t=1; t<4; t++){
		hitt= colision_enemigos(enemigo[t], enemigo[0]);

		if (hitt==1){
		break;
		}
	}




	if ((hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8) || (hitt==1)){
	enemigo[0].x=enem_x;
 	enemigo[0].y=enem_y;

	srand (time(NULL));
	dir1= rand()%4;
	}

}

int mover_enemigo2(){

	int enem_x=enemigo[1].x;
 	int enem_y=enemigo[1].y;
	int hit=0;

	if (dir2==0){
		enemigo[1].y-=2;
		dirtenemigo2+=1;

	}
	if (dir2==1){
		enemigo[1].y+=2;
		dirtenemigo2+=1;
	}
	if (dir2==2){
		enemigo[1].x+=2;
		dirtenemigo2+=1;
	}
	if (dir2==3){
		enemigo[1].x-=2;
		dirtenemigo2+=1;
	}
	if(32 >= enemigo[1].x   || enemigo[1].x +25 >= 440){
	enemigo[1].x=enem_x;
 	enemigo[1].y=enem_y;

	srand (time(NULL));
	dir2= rand()%4;
	}
	if ( 32 >= enemigo[1].y   || enemigo[1].y + 26>=440){

	enemigo[1].x=enem_x;
 	enemigo[1].y=enem_y;
	srand (time(NULL));
	dir2= rand()%4;
	}

	int i=0;
	for(i=0; i<200; i++){
		hit= colision_enemigo_mapa(bloque[i], enemigo[1]);

		if (hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8 ){
		break;
		}
	}

	int t;
	int hitt=0;
	for(t=0; t<4; t++){
		if(t!=1){		
		hitt= colision_enemigos(enemigo[t], enemigo[1]);

		if (hitt==1){
		break;
		}}
	}
	
	if ((hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8) || (hitt==1)){
	enemigo[1].x=enem_x;
 	enemigo[1].y=enem_y;

	srand (time(NULL));
	dir2= rand()%4;
	}

}

int cambio=0;
int mover_enemigo3(){

	int enem_x=enemigo[2].x;
 	int enem_y=enemigo[2].y;
	int hit=0;

	if (dir3==0){
		enemigo[2].y-=1;
		cambio+=1;
		dirtenemigo3+=1;
	}


	if (dir3==1){
		enemigo[2].y+=1;
		cambio+=1;
		dirtenemigo3+=1;
	}



	if (dir3==2){
		enemigo[2].x+=1;
		cambio+=1;
		dirtenemigo3+=1;
	}

	if (dir3==3){
		enemigo[2].x-=1;
		cambio+=1;
		dirtenemigo3+=1;
	}
	
	if(32 >= enemigo[2].x   || enemigo[2].x +25 >= 440){
	enemigo[2].x=enem_x;
 	enemigo[2].y=enem_y;

	srand (time(NULL));
	dir3= rand()%4;
	}
	if ( 32 >= enemigo[2].y   || enemigo[2].y + 26>=440){

	enemigo[2].x=enem_x;
 	enemigo[2].y=enem_y;
	srand (time(NULL));
	dir3= rand()%4;
	}

	int i=0;
	for(i=0; i<200; i++){
		hit= colision_enemigo_mapa(bloque[i], enemigo[2]);

		if (hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8 ){

		break;
		}
	}
	
	int t;
	int hitt=0;
	for(t=0; t<4; t++){
		if(t!=2){		
		hitt= colision_enemigos(enemigo[t], enemigo[2]);

		if (hitt==1){
		break;
		}}
	}
	
	if ((hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8) || (hitt==1)){
	enemigo[2].x=enem_x;
 	enemigo[2].y=enem_y;
	
	srand (time(NULL));
	dir3= rand()%4;
	}

}

static void mover_enemigo4(){

	int enem_x=enemigo[3].x;
 	int enem_y=enemigo[3].y;
	int hit=0;

	if (dir4==0){
		enemigo[3].y-=1;
		dirtenemigo4+=1;

	}


	if (dir4==1){
		enemigo[3].y+=1;
		dirtenemigo4+=1;
	}



	if (dir4==2){
		enemigo[3].x+=1;
		dirtenemigo4+=1;
	}

	if (dir4==3){
		enemigo[3].x-=1;
		dirtenemigo4+=1;
	}
	if(32 >= enemigo[3].x   || enemigo[3].x +25 >= 440){
	enemigo[3].x=enem_x;
 	enemigo[3].y=enem_y;

	srand (time(NULL));
	dir4= rand()%4;
	}
	if ( 32 >= enemigo[3].y   || enemigo[3].y + 26>=440){

	enemigo[3].x=enem_x;
 	enemigo[3].y=enem_y;
	srand (time(NULL));
	dir4= rand()%4;
	}

	int i=0;
	for(i=0; i<200; i++){
		hit= colision_enemigo_mapa(bloque[i], enemigo[3]);

		if (hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8 ){
		break;
		}
	}
	
	int t;
	int hitt=0;
	for(t=0; t<4; t++){
		if(t!=3 && t!=0){		
		hitt= colision_enemigos(enemigo[t], enemigo[3]);

		if (hitt==1){
		break;
		}}
	}
	
	if ((hit==1 && bloque[i].tipo !=7 && bloque[i].tipo !=8 ) || (hitt==1)){
	enemigo[3].x=enem_x;
 	enemigo[3].y=enem_y;
	srand (time(NULL));
	dir4= rand()%4;
	}

}





static void estructura_bandera() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 464+8;
	src.y = 352;
	src.w = 32;
	src.h = 32;

	dest.x = 464;
	dest.y = 352;
	dest.w = 32;
	dest.h = 32;

	SDL_BlitSurface(bandera, NULL, pantalla,&src);
	SDL_SetColorKey(bandera,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(bandera->format,255,255,255));


	src.x = 464;
	src.y = 16;
	src.w = 16;
	src.h = 16;

	dest.x = 464;
	dest.y = 16;
	dest.w = 16;
	dest.h = 16;

	SDL_BlitSurface(enemigos, NULL, pantalla,&src);
	SDL_SetColorKey(enemigos,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(enemigos->format,255,255,255));

}

static void niveles(){
	SDL_Rect src;
	SDL_Rect dest;

	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = 448;
	dest.y = 384;
	dest.w = 64;
	dest.h = 64;

	if(mapa==1){
	src.x = 64;
	}
	if(mapa==2){
	src.x = 120;
	}
	if(mapa==3){
	src.x = 180;
	}

	SDL_BlitSurface(numero, &src, pantalla, &dest);


}

static void estructura_vidas() {


	SDL_Rect src;
	SDL_Rect dest;

	
	src.x = 448+8;
	src.y = 160;
	src.w = 34;
	src.h = 16;

	dest.x = 448;
	dest.y = 160;
	dest.w = 64;
	dest.h = 16;

	SDL_BlitSurface(jugador, NULL, pantalla,&src);
	SDL_SetColorKey(jugador,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(jugador->format,0,0,0));

}


static void Jproteccion(){

	if(dist_proteccion<200){	
	SDL_Rect src;
	src.x = tanque.x;
	src.y = tanque.y;
	src.w = tanque.w;
	src.h = tanque.h;
	SDL_BlitSurface(proteccion, NULL, pantalla,&src);
	SDL_SetColorKey(proteccion,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(proteccion->format,0,0,0));
	}

}


static void in_poder(){

	SDL_Rect src;
	src.x = poder[0].x;
	src.y = poder[0].y;
	src.w = poder[0].w;
	src.h = poder[0].h;
	SDL_BlitSurface(poder_pala, NULL, pantalla,&src);

	src.x = poder[1].x;
	src.y = poder[1].y;
	src.w = poder[1].w;
	src.h = poder[1].h;
	SDL_BlitSurface(poder_granada, NULL, pantalla,&src);


	src.x = poder[2].x;
	src.y = poder[2].y;
	src.w = poder[2].w;
	src.h = poder[2].h;
	SDL_BlitSurface(poder_tiempo, NULL, pantalla,&src);


}

int x;
int y;
int poderON=0;
int tipo;
static void J(){

	if(poderON==0){
 	srand (time(NULL));
	x= 32 + rand()%384;
	y= 32 + rand()%384;
	tipo= rand()%3;
	poder[tipo].x=x;
	poder[tipo].y=y;
	poder[tipo].w=32;
	poder[tipo].h=32;
	poder[tipo].tipo=tipo;

	poderON=1;
	}

	SDL_Rect src;
	src.x = poder[tipo].x;
	src.y = poder[tipo].y;
	src.w = poder[tipo].w;
	src.h = poder[tipo].h;

	if (tipo==0){
	SDL_BlitSurface(poder_pala, NULL, pantalla,&src);
	poder[1].x=800;
	poder[2].x=800;
	}

	if (tipo==1){
	SDL_BlitSurface(poder_granada, NULL, pantalla,&src);
	poder[0].x=800;
	poder[2].x=800;
	}
	if (tipo==2){
	SDL_BlitSurface(poder_tiempo, NULL, pantalla,&src);
	poder[0].x=800;
	poder[1].x=800;
	}

}


int colision_poder(poder_t a, tanque_t b) {

	int izq_a, izq_b;
	int der_a, der_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izq_a = a.x;
	der_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izq_b = b.x;
	der_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;


	if (izq_a > der_b) {
		return 0;
	}

	if (der_a < izq_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	return 1;
}




static void poderpala(){
	int hit=colision_poder(poder[0], tanque);
	
	if(hit==1){
	poder[0].x=800;
	dist_p=0;
	}
	
	if(dist_p<=450){
	bloque[0].tipo = 5;
	bloque[1].tipo = 5;
	bloque[3].tipo = 6;
	
	bloque[0].x = 208;
	bloque[0].y = 400;
	bloque[1].x = 256;
	bloque[1].y = 400;
	bloque[3].x = 224;
	bloque[3].y = 400;
	}
	else{
	bloque[0].tipo = 2;
	bloque[1].tipo = 2;
	bloque[3].tipo = 3;
	bloque[3].tipo = 0;
	


	}
}

static void podergranada(){
	int hit=colision_poder(poder[1], tanque);
	
	if(hit==1){
	poder[1].x=800;
	puntaje+=3;
	enemigo[0].x=33;
	enemigo[0].y=33;
	enemigo[1].x=227;
	enemigo[1].y=34;
	enemigo[2].x=418;
	enemigo[2].y=34;
	if(mapa!=1){	
	enemigo[3].x=33;
	enemigo[3].y=33;}

	}

}

int tiempoON=0;
static void podertiempo(){
	int hit=colision_poder(poder[2], tanque);
	
	if(hit==1){
	poder[2].x=800;
	dist_Jtiempo=0;
	tiempoON=1;
	}

	if(dist_Jtiempo<=200){
	tiempoON=1;
	}
	else{
	tiempoON=0;
	}

}





int main() {


//LLamar las graficas
	SDL_Surface *temp;
	
	
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);
	pantalla = SDL_SetVideoMode(512, 480, 8,SDL_DOUBLEBUF);
	
	if (pantalla == NULL) {

		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	temp = SDL_LoadBMP("numero.bmp");

	if (temp == NULL) {

		printf("Unable to load numero.bmp.\n");
		return 1;
	}
	Uint32 colorkey = SDL_MapRGB(temp->format, 255, 0, 255);
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, colorkey);


	numero = SDL_DisplayFormat(temp);

	if (numero == NULL) {

		printf("Unable to convert bitmap.\n");
		return 1;
	}

	SDL_FreeSurface(temp);
	temp = SDL_LoadBMP("titulo.bmp");

	if (temp == NULL) {

		printf("Unable to load numero.bmp.\n");
		return 1;
	}

	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, colorkey);

	titulo = SDL_DisplayFormat(temp);

	if (numero == NULL) {

		printf("Unable to convert bitmap.\n");
		return 1;
	}

	SDL_FreeSurface(temp);

	temp = SDL_LoadBMP("perder.bmp");

	if (temp == NULL) {

		printf("Unable to load perder.bmp.\n");
		return 1;
	}

	perder = SDL_DisplayFormat(temp);

	if (perder == NULL) {

		printf("Unable to convert bitmap.\n");
		return 1;
	}
	

	SDL_FreeSurface(temp);

	muro_ladrillo2 = SDL_LoadBMP("muro_ladrillo2.bmp");

	muro_ladrillo2 = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	arbol2 = SDL_LoadBMP("arbol2.bmp");

	arbol2 = SDL_DisplayFormat(temp);
	SDL_SetColorKey(arbol2,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(arbol2->format,0,0,0));


	SDL_FreeSurface(temp);

	muro_hierro2 = SDL_LoadBMP("muro_hierro2.bmp");

	muro_hierro2 = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	muro_ladrillo_delgado = SDL_LoadBMP("muro_ladrillo_delgado.bmp");

	muro_ladrillo_delgado = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	base = SDL_LoadBMP("emblema.bmp");

	base = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	Jtanque_arriba = SDL_LoadBMP("Jtanque_arriba.bmp");

	Jtanque_arriba = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	Jtanque_abajo = SDL_LoadBMP("Jtanque_abajo.bmp");

	Jtanque_abajo = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	Jtanque_izq = SDL_LoadBMP("Jtanque_izq.bmp");

	Jtanque_izq = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	Jtanque_der = SDL_LoadBMP("Jtanque_der.bmp");

	Jtanque_der = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	bandera = SDL_LoadBMP("bandera.bmp");

	bandera = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	jugador = SDL_LoadBMP("jugador.bmp");

	jugador = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	base_destruida = SDL_LoadBMP("base_destruida.bmp");

	base_destruida = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	perder = SDL_LoadBMP("perder.bmp");

	perder = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	victoria = SDL_LoadBMP("victoria.bmp");

	victoria = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_basico_arriba = SDL_LoadBMP("tanque_basico_arriba.bmp");

	tanque_basico_arriba = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_basico_abajo = SDL_LoadBMP("tanque_basico_abajo.bmp");

	tanque_basico_abajo = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_basico_izq = SDL_LoadBMP("tanque_basico_izq.bmp");

	tanque_basico_izq = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_basico_der = SDL_LoadBMP("tanque_basico_der.bmp");

	tanque_basico_der = SDL_DisplayFormat(temp);



	SDL_FreeSurface(temp);

	tanque_basico2_arriba = SDL_LoadBMP("tanque_basico2_arriba.bmp");

	tanque_basico2_arriba = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_basico2_abajo = SDL_LoadBMP("tanque_basico2_abajo.bmp");

	tanque_basico2_abajo = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_basico2_izq = SDL_LoadBMP("tanque_basico2_izq.bmp");

	tanque_basico2_izq = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_basico2_der = SDL_LoadBMP("tanque_basico2_der.bmp");

	tanque_basico2_der = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_rapido_arriba = SDL_LoadBMP("tanque_rapido_arriba.bmp");

	tanque_rapido_arriba = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_rapido_abajo = SDL_LoadBMP("tanque_rapido_abajo.bmp");

	tanque_rapido_abajo = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_rapido_izq = SDL_LoadBMP("tanque_rapido_izq.bmp");

	tanque_rapido_izq = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_rapido_der = SDL_LoadBMP("tanque_rapido_der.bmp");

	tanque_rapido_der = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	enemigos = SDL_LoadBMP("enemigos.bmp");

	enemigos = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	proteccion = SDL_LoadBMP("proteccion.bmp");

	proteccion = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	poder_casco = SDL_LoadBMP("poder_casco.bmp");

	poder_casco = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	poder_granada = SDL_LoadBMP("poder_granada.bmp");

	poder_granada = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	poder_pala = SDL_LoadBMP("poder_pala.bmp");

	poder_pala = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	poder_tiempo = SDL_LoadBMP("poder_tiempo.bmp");

	poder_tiempo = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);

	muro_hierro_delgado = SDL_LoadBMP("muro_hierro_delgado.bmp");

	muro_hierro_delgado = SDL_DisplayFormat(temp);


	SDL_FreeSurface(temp);

	tanque_blindado_der_c0 = SDL_LoadBMP("tanque_blindado_der_c0.bmp");

	tanque_blindado_der_c0 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_der_c1 = SDL_LoadBMP("tanque_blindado_der_c1.bmp");

	tanque_blindado_der_c1 = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);

	tanque_blindado_der_c2 = SDL_LoadBMP("tanque_blindado_der_c2.bmp");

	tanque_blindado_der_c2 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_der_c3 = SDL_LoadBMP("tanque_blindado_der_c3.bmp");

	tanque_blindado_der_c3 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_izq_c0 = SDL_LoadBMP("tanque_blindado_izq_c0.bmp");

	tanque_blindado_izq_c0 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_izq_c1 = SDL_LoadBMP("tanque_blindado_izq_c1.bmp");

	tanque_blindado_izq_c1 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_izq_c2 = SDL_LoadBMP("tanque_blindado_izq_c2.bmp");

	tanque_blindado_izq_c2 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_izq_c3 = SDL_LoadBMP("tanque_blindado_izq_c3.bmp");

	tanque_blindado_izq_c3 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_arriba_c0 = SDL_LoadBMP("ttanque_blindado_arriba_c0.bmp");

	tanque_blindado_arriba_c0 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_arriba_c1 = SDL_LoadBMP("tanque_blindado_arriba_c1.bmp");

	tanque_blindado_arriba_c1 = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);

	tanque_blindado_arriba_c2 = SDL_LoadBMP("tanque_blindado_arriba_c2.bmp");

	tanque_blindado_arriba_c2 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_arriba_c3 = SDL_LoadBMP("tanque_blindado_arriba_c3.bmp");

	tanque_blindado_arriba_c3 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_abajo_c0 = SDL_LoadBMP("tanque_blindado_abajo_c0.bmp");

	tanque_blindado_abajo_c0 = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);

	tanque_blindado_abajo_c1 = SDL_LoadBMP("tanque_blindado_abajo_c1.bmp");

	tanque_blindado_abajo_c1 = SDL_DisplayFormat(temp);
	
	SDL_FreeSurface(temp);

	tanque_blindado_abajo_c2 = SDL_LoadBMP("tanque_blindado_abajo_c2.bmp");

	tanque_blindado_abajo_c2 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	tanque_blindado_abajo_c3 = SDL_LoadBMP("ttanque_blindado_abajo_c3.bmp");

	tanque_blindado_abajo_c3 = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	arbol = SDL_LoadBMP("arbol.bmp");

	arbol = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	muro_ladrillo = SDL_LoadBMP("muro_ladrillo.bmp");

	muro_ladrillo = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	muro_hierro = SDL_LoadBMP("muro_hierro.bmp");

	muro_hierro = SDL_DisplayFormat(temp);



	//Initialize the ball position data. 
	in_tanque();
	in_bala();
	in_bala1();
	in_bala2();
	in_bala3();
	in_bala4();
	int quit = 0; 
	int state = 0;
	Uint8 *keystate = 0;
	Uint32 next_game_tick = SDL_GetTicks();
	int sleep = 0;
	int dir=0;
	int veces=1;
	int veces1=1;
	int ultimadir=0;

        // Animate 
	while (quit == 0) {

		// Update SDL's internal input state information. 
		SDL_PumpEvents();

		// Grab a snapshot of the keyboard. 
		keystate = SDL_GetKeyState(NULL);

		//Respond to input. 
		if (keystate[SDLK_ESCAPE]) {
			quit = 1;
		}


		if (keystate[SDLK_UP]) {
			estructura_tanquearriba();
			mover_tanque(0);
			dir=0;

		}
		if (keystate[SDLK_DOWN]) {
			estructura_tanqueabajo();
			mover_tanque(1);
			dir=1;
			ultimadir=1;

		}
		if (keystate[SDLK_RIGHT]) {
			estructura_tanqueder();
			mover_tanque(2);
			dir=2;
			ultimadir=2;

		}
		if (keystate[SDLK_LEFT]) {
			estructura_tanqueizq();
			mover_tanque(3);
			dir=3;
			ultimadir=3;

		}
		if (keystate[SDLK_d]) {

			if(tiro==0){
			pos_in_tanque(dir);
			tiro=1;
			}

		}

		//Definir el fondo
		estructura_fondo();

		//Desplegar menu
		if (state == 0 ) {

			if (keystate[SDLK_SPACE]) {
				state = 1;

			}

			//Mostrar menu
			estructura_menu();
		}

		//display gameover
		else if (state == 2) {
			
			if(r == 1 || r == 2){estructura_perder_ganar();}
			


		} else if (state == 1){


			if (r == 1 || r == 2) {

				state = 2;

			} else if (r == 2){

				state = 2;
			}


			//estructura tanque
			if (dir==0){
			estructura_tanquearriba();
			}
			else if (dir==1){
			estructura_tanqueabajo();
			}
			else if (dir==2){
			estructura_tanqueder();
			}
			else if (dir==3){
			estructura_tanqueizq();
			}



			if(mapa==1){
				if(dir1==0){
				estructura_enemigo_arriba(0);
				}
				if(dir1==1){
				estructura_enemigo_abajo(0);
				}
				if(dir1==2){
				estructura_enemigo_der(0);
				}
				if(dir1==3){
				estructura_enemigo_izq(0);
				}
			}
			if(mapa!=1){
				if(dir4==0){
				estructura_enemigo_arriba(3);
				}
				if(dir4==1){
				estructura_enemigo_abajo(3);
				}
				if(dir4==2){
				estructura_enemigo_der(3);
				}
				if(dir4==3){
				estructura_enemigo_izq(3);
				}
			}

			if(dir2==0){
			estructura_enemigo_arriba(1);
			}
			if(dir2==1){
			estructura_enemigo_abajo(1);
			}
			if(dir2==2){
			estructura_enemigo_der(1);
			}
			if(dir2==3){
			estructura_enemigo_izq(1);
			}


			if(dir3==0){
			estructura_enemigo_arriba(2);
			}
			if(dir3==1){
			estructura_enemigo_abajo(2);
			}
			if(dir3==2){
			estructura_enemigo_der(2);
			}
			if(dir3==3){
			estructura_enemigo_izq(2);
			}

			estructura_mapa();
			marco();
			in_poder();
			while(veces==1){
			base1();
			in_mapa1();
			veces=0;
			J();
			}
			
			//Disparo enemigo0
			if(dirtenemigo1==80){tiro1=1; dirtenemigo1=0;pos_in_bala_enemigo(0);}

			if(tiro1==1){
			tiro_enemigo_map(0);
			}

			//Disparo enemigo1
			if(dirtenemigo2==120){tiro2=1; dirtenemigo2=0;pos_in_bala_enemigo(1);}

			if(tiro2==1){
			tiro_enemigo_map(1);
			}

			//Disparo enemigo2
			if(dirtenemigo3==80){tiro3=1; dirtenemigo3=0;pos_in_bala_enemigo(2);}

			if(tiro3==1){
			tiro_enemigo_map(2);
			}

			//Disparo enemigo3
			if(dirtenemigo4==100){tiro4=1; dirtenemigo4=0;pos_in_bala_enemigo(3);}

			if(tiro4==1){
			tiro_enemigo_map(3);
			}

		
			bala_hit_tanque(0);
			bala_hit_tanque(1);
			bala_hit_tanque(2);
			bala_hit_tanque(3);


			if(tiro==1){
			disparo(dirtiro);
			}
			
			tanque_enemigo();
			if(vidas==2){r=1;}			
			

			Jproteccion();
			estructura_bala();
			marcador_vidas();
			niveles();

			if(puntaje==3 || puntaje>=3){
			mapa+=1;
			clean_map();
			poderON=0;
			dist_p=500;
			dist_Jtiempo=500;
			J();	
			dist_proteccion=0;
			tipo= rand()%3;
				if(mapa==2){
				puntaje=0;
				in_tanque();
				in_mapa2();
				base1();

				}
				if(mapa==3){
				puntaje=0;
				in_tanque();
				in_mapa3();
				base1();
				}
				if(mapa==4){
				r=2;
				}

			}

			estructura_bandera();
			estructura_vidas();

			poderpala();
			podergranada();
			podertiempo();
			if(mapa==1){
			balahit1();
			if(balahit==1){
			in_bala();
			balahit=0;
			}}

			balahit2();
			if(balahit==1){
			in_bala();
			balahit=0;
			}

			balahit3();
			if(balahit==1){
			in_bala();
			balahit=0;
			}
	
			balahit4();
			if(balahit==1){
			in_bala();
			balahit=0;
			}

			if(tiempoON==0){
			if(mapa==1){			
			mover_enemigo1();
			}
			mover_enemigo2();
			mover_enemigo3();
			if(cambio==32){
				if(enemigo[2].clase==2){ enemigo[2].clase=0;}
				else{ enemigo[2].clase=2;}
				cambio=0;
			}


			if(mapa!=1){			
			mover_enemigo4();}
			}

		}

		//Ask SDL to update the entire pantalla
		SDL_Flip(pantalla);

		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();

		if( sleep >= 0 ) {

            		SDL_Delay(sleep);
        	}
	}

	return 0;
}















