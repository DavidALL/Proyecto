typedef struct Nodo
{
	Elem dato;
	struct Nodo *ant;
	struct Nodo *sig;
}*ApNodo;

typedef struct cNodo
{
	ApNodo izq;
	ApNodo der;
}*Bicola;

int esNuevab(Bicola);
Elem elemd(Bicola);
Elem elemi(Bicola);
int numElem(Bicola);

Bicola nuevab()
{ 
	Bicola q = (Bicola)malloc(sizeof(struct cNodo));
	q->izq = NULL;
	q->der = NULL;
	return q;
}

Bicola formard(Bicola q, Elem e)
{
	ApNodo t = (ApNodo)malloc(sizeof(struct Nodo));
	t -> dato = e;
	if(esNuevab(q))
	{
		t->ant = NULL;
		t->sig = NULL;
		q->izq = t;
		q->der = t;
	}
	else
	{
		q->der->sig = t;
		t->ant = q->der;
		t->sig = NULL;
		q->der = t;
	}
	return q;
}

Bicola formari(Elem e, Bicola q)
{
	ApNodo t = (ApNodo)malloc(sizeof(struct Nodo));
	t -> dato = e;
	if(esNuevab(q))
	{
		t->ant = NULL;
		t->sig = NULL;
		q->izq = t;
		q->der = t;
	}
	else
	{
		q->izq->ant = t;
		t->sig = q->izq;
		t->ant = NULL;
		q->izq = t;
	}
	return q;
}

int esNuevab(Bicola q)
{
  return q->izq == NULL && q->der == NULL;
}

Elem elemd(Bicola q)
{
  return q->der->dato;
}

Elem elemi(Bicola q)
{
  return q->izq->dato;
}

Bicola desformard(Bicola q)
{ 
	if(numElem(q) == 0 || numElem(q) == 1)
	{
		return NULL;
	}
	else
	{
		q->der = q->der->ant;
		q->der->sig = NULL;
	}
	return q; 
}

Bicola desformari(Bicola q)
{
	if(numElem(q) == 0 || numElem(q) == 1)
	{
		return NULL;
	}
	else
	{
		q->izq = q->izq->sig;
		q->izq->ant = NULL;
	}
	return q; 
}

void impID(Bicola q)
{
	ApNodo c = q->izq;
	while(c != NULL)
	{
		impElem(c->dato);
		c = c->sig;
	}
}

void impDI(Bicola q)
{
	ApNodo c=q->der;
	while(c!=NULL)
	{
		impElem(c->dato);
		c=c->ant;
	}
}

int numElem(Bicola q)
{
	ApNodo t = q->izq;
	int i = 0;
	while(t)
	{
		i++;
		t = t->sig;
	}
	return i;
}

void intercambiar(Bicola q, int pos1, int pos2)
{
	if(pos1 <= numElem(q) && pos2 <= numElem(q))
	{
		ApNodo ap1 = q->izq;
		ApNodo ap2 = q->izq;
		Elem aux; int i;
		for(i = 1; i < pos1; i++) ap1 = ap1->sig;
		for(i = 1; i < pos2; i++) ap2 = ap2->sig;
		aux = igualaElem(ap1->dato); 
		ap1->dato = ap2->dato;
		ap2->dato = aux;
	}
	else puts("Posiciones invalidas");
}

Elem mayor(Bicola q)
{
	Elem mayor = igualaElem(q->izq->dato);
	Elem valor;
	ApNodo cent = q->izq;
	while(cent)
	{
		valor = igualaElem(cent->dato);
		if(esMayoroIgual(valor, mayor))
			mayor = igualaElem(valor);
		cent = cent->sig;
	}
	return mayor;
}

int existe(Bicola q, Elem e)
{
	Elem valor;
	ApNodo cent = q->izq;
	while(cent)
	{
		valor = igualaElem(cent->dato);
		if(esMenoroIgual(valor, e) && esMayoroIgual(valor, e))
			return 1;
		cent = cent->sig;
	}
	return 0;
}

Bicola EncontrarDI(int pos, Bicola q)
{
	Bicola aux = q;
	int i = 0;

	if(pos >= numElem(q))
	{
		puts("Posicion invalda");
		return q;
	}
	
	while(i < pos)
	{
		aux = desformard(aux);
		i++;
	}
	return aux;
}

Bicola EncontrarID(int pos, Bicola q)
{
	Bicola aux = q;
	int i = 0;

	if(pos >= numElem(q))
	{
		puts("Posicion invalda");
		return q;
	}
	
	while(i < pos)
	{
		aux = desformari(aux);
		i++;
	}
	return aux;
}

Elem datoDI(int pos, Bicola q)
{
	ApNodo cent = q->der;
	int i = 0;
	
	while(i < pos-1)
	{
		cent = cent -> ant;
		i++;
	}
	return cent->dato;
}

Elem datoID(int pos, Bicola q)
{
	ApNodo cent = q->izq;
	int i = 0;
	
	while(i<pos-1)
	{
		cent = cent -> sig;
		i++;
	}
	return cent->dato;
}

void EscDI(int pos, int valor, Bicola q)
{
	ApNodo cent = q->der;
	int i = 0;
	
	while(i < pos-1)
	{
		cent = cent -> ant;
		i++;
	}
	cent->dato = valor;
}

void esperar(void)
{
  fflush(stdin);
  getchar();
}

void limp(void)
{
  system("clear");
}
