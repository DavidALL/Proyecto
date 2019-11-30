typedef int Elem;

void impElem(Elem e)
{
  printf("%d\n", e);
}

int esMenoroIgual(Elem e1, Elem e2)
{
  return e1 <= e2;
}

int esMayoroIgual(Elem e1, Elem e2)
{
  return e1 >= e2;
}

Elem igualaElem(Elem e){ return e; }
