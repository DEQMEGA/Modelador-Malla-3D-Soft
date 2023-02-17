


#include "Render2023-v1.h"

const unsigned int Ancho = 640;
const unsigned int Alto  = 480;
const unsigned int AnchoM = 640>>1;
const unsigned int AltoM  = 480>>1;

#include "Vista.h"

static char StepWrite = 0;

struct VERTEX Puntero = {0,0};
struct VERTEX TempV0  = {0,0};
struct VERTEX TempV1  = {0,0};
struct VERTEX TempV2  = {0,0};

static int Velocidad = 5;

void Bucle( register unsigned int *BufferVideo, int Fps, int DeltaTime ){
	ClearScreen(0);
	DrawGrilla_Z();
	if (GetKey(VK_ESCAPE)) SetLoopNull();// ESCAPE
	if (GetKeyOnce(32)){
		if (StepWrite==0){TempV0 = Puntero;StepWrite=1;/*goto END_ADD;*/} else
		if (StepWrite==1){TempV1 = Puntero;StepWrite=2;/*goto END_ADD;*/} else
		if (StepWrite==2){
			TempV2 = Puntero;

			// if( TempV0.Y > TempV1.Y ){ SWAP1(TempV0.X,TempV1.X); SWAP1(TempV0.Y,TempV1.Y); SWAP1(TempV0.Z,TempV1.Z); }
		    // if( TempV0.Y > TempV2.Y ){ SWAP1(TempV0.X,TempV2.X); SWAP1(TempV0.Y,TempV2.Y); SWAP1(TempV0.Z,TempV2.Z); }
		    // if( TempV1.Y > TempV2.Y ){ SWAP1(TempV1.X,TempV2.X); SWAP1(TempV1.Y,TempV2.Y); SWAP1(TempV1.Z,TempV2.Z); }

			AddPolygon(
				TempV0.X,-TempV0.Y,TempV0.Z,
				TempV1.X,-TempV1.Y,TempV1.Z,
				TempV2.X,-TempV2.Y,TempV2.Z,
				0xffffffff
			);
			StepWrite=0;
		}
	}
	// END_ADD:
	if (GetKeyOnce(VK_RIGHT)){ Puntero.X++; }
	if (GetKeyOnce(VK_LEFT) ){ Puntero.X--; }
	if (GetKeyOnce(VK_UP)   ){ Puntero.Y++; }
	if (GetKeyOnce(VK_DOWN) ){ Puntero.Y--; }
	if (GetKeyOnce('e') ){ Puntero.Z++; }
	if (GetKeyOnce('q') ){ Puntero.Z--; }

	if (GetKey('a')) rot0+=Velocidad;
	if (GetKey('d')) rot0-=Velocidad;
	if (GetKey('w')) rot1+=Velocidad;
	if (GetKey('s')) rot1-=Velocidad;
	if (GetKey('x')) SUM+=Velocidad;
	if (GetKey('z')) SUM-=Velocidad;

	DrawMalla();

	Cuadro(
		(Puntero.X+16) << 3,
		(16-Puntero.Y) << 3,
		2,
		0xffff0000
	);

	// rot0+=Velocidad;
	// rot1+=Velocidad;

	printf("\rPOS: [%i,%i,%i]      ", Puntero.X, Puntero.Y, Puntero.Z );
}

void LoadCube( int Xpos, int Ypos, int Zpos, int Tam ){
	if(Tam==0) Tam = 64;
	struct VERTEX CubeVertex1[8] = {
	   { Tam, Tam,-Tam},
	   {-Tam, Tam,-Tam},
	   { Tam, Tam, Tam},
	   { Tam,-Tam, Tam},
	   {-Tam,-Tam, Tam},
	   {-Tam, Tam, Tam},
	   {-Tam,-Tam,-Tam},
	   { Tam,-Tam,-Tam}
	};
	unsigned int CubeFaces1[12*3] = {
		1, 2, 3,
		4, 3, 5,
		5, 6, 7,
		7, 8, 5,
		8, 1, 4,
		7, 2, 8,
		3, 2, 6,
		5, 3, 6,
		7, 6, 2,
		5, 8, 4,
		4, 1, 3,
		8, 2, 1
	};
	register unsigned int *_F_ = CubeFaces1;
	for (unsigned int i = 0; i < 12; ++i){
		const unsigned int A = *(_F_+0)-1;
		const unsigned int B = *(_F_+1)-1;
		const unsigned int C = *(_F_+2)-1;
		AddPolygon(
			CubeVertex1[ A ].X + Xpos, CubeVertex1[ A ].Y + Ypos, CubeVertex1[ A ].Z + Zpos,
			CubeVertex1[ B ].X + Xpos, CubeVertex1[ B ].Y + Ypos, CubeVertex1[ B ].Z + Zpos,
			CubeVertex1[ C ].X + Xpos, CubeVertex1[ C ].Y + Ypos, CubeVertex1[ C ].Z + Zpos,
			COLOR_RGB(
				rand()%0xff,
				rand()%0xff,
				rand()%0xff
			)
		);
		_F_+=3;
	}
}

int main(void){
	CrearScreen( Ancho,Alto );
	SetLoop(Bucle);
	LoadCube( 0,0,0, 64 );
	LoadCube( 16,0,0, 16 );
	StepWrite = 0;
    StartLoop();
	return 0;
}