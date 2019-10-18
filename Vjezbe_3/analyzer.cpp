#include <ElementaryParticle.h>

int main()
{
	ElementaryParticle *Higgs;

	Higgs=new ElementaryParticle("Higgs", 125, true);

	Higgs->ParticleMomentum(32, 22, 45);

	Higgs->transMomentum();

	return 0;
}