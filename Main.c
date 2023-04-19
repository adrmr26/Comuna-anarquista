struct Requiere {
	char Area[10];
	int Tiempo;
	int Bateria;
};

int main(){
	struct Requiere s1 ={"Gym",12,11};
	
	printf("%s %d %d", s1.Area, s1.Bateria, s1.Tiempo);
	return 0;
}
