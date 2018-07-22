#include <stdio.h>
#include <stdlib.h>
#include <mytypes.h>

/* xmldoc
 * <problem>
 *      <description>
 *          There exists exactly one Pythagorean triplet for which a + b + c =
 *          1000.
 *          Find the product abc.
 *      </description>
 *      <insight>
 *          All the primitive triplets can be generated by choosing the first
 *          parent as 3,4,5 and recursively using the following three
 *          transformation to generate 3 children for each primitive triplet.
 *          T1:     a - 2b + 2c       2a - b + 2c     2a - 2b + 3c 
 *          T2:     a + 2b + 2c       2a + b + 2c     2a + 2b + 3c
 *          T3:    -a + 2b + 2c      -2a + b + 2c    -2a + 2b + 3c
 *      </insight>
 *      <solution>
 *          Without programming:
 *
 *          a= 2mn; b= m^2 -n^2; c= m^2 + n^2;
 *          a + b + c = 1000;
 *
 *          2mn + (m^2 -n^2) + (m^2 + n^2) = 1000;
 *          2mn + 2m^2 = 1000;
 *          2m(m+n) = 1000;
 *          m(m+n) = 500;
 *
 *          m>n;
 *
 *          m= 20; n= 5;
 *
 *          a= 200; b= 375; c= 425;
 *      </solution>
 * </problem>
 */
struct ptriplet {
    u32 a;
    u32 b;
    u32 c;
};
typedef struct ptriplet ptriplet_t, *ptriplet_p;

#define MAX_TRIPLETS 1000

ptriplet_t alltriplets[ MAX_TRIPLETS ];
u32 triplets = 0;

static u32 storetriplet( ptriplet_t t )
{
    if( triplets >= MAX_TRIPLETS ) {
        return 0;
    } else {
        alltriplets[triplets] = t;
        triplets++;
        return 1;
    }
}

u32 genchild( ptriplet_t par, ptriplet_t child[3] )
{
    ptriplet_t localchild[3];
    u32 i;

    child[0].a = par.a - 2 * par.b + 2 * par.c;
    child[1].a = par.a + 2 * par.b + 2 * par.c;
    child[2].a = - par.a + 2 * par.b + 2 * par.c;
    child[0].b = 2 * par.a - par.b + 2 * par.c;
    child[1].b = 2 * par.a + par.b + 2 * par.c;
    child[2].b = - 2 * par.a + par.b + 2 * par.c;
    child[0].c = 2 * par.a - 2 * par.b + 3 * par.c;
    child[1].c = 2 * par.a + 2 * par.b + 3 * par.c;
    child[2].c = - 2 * par.a + 2 * par.b + 3 * par.c;
    if ( storetriplet( child[0] ) && storetriplet( child[1] ) && \
            storetriplet( child[2] ) ) {
        localchild[0] = child[0];
        localchild[1] = child[1];
        localchild[2] = child[2];
        for( i = 0; i < 3; i++ ) {
            genchild( localchild[0], child );
        }
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    ptriplet_t par, child[3];
    u32 i, sum;

    par.a = 3; par.b = 4; par.c = 5;
    storetriplet( par );
    genchild( par, child );
    for( i = 0; i < MAX_TRIPLETS; i++ ) {
        sum = alltriplets[i].a + alltriplets[i].b + alltriplets[i].c;
        printf("The pythogorean Triplet is %u %u %u sum is %u\n", alltriplets[i].a, 
                alltriplets[i].b, alltriplets[i].c, sum);
        if( (1000 % sum) == 0 ) {
            break;
        }
    }
    printf("The pythogorean Triplet is %u %u %u by %u\n", alltriplets[i].a, 
            alltriplets[i].b, alltriplets[i].c, 1000 / sum);
}