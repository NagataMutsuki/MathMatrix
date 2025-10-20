#include<stdio.h>
#include<stdlib.h>
#define MENUNUMBER 7
#define size 5

//行列の出力
void outputMatrix(int r, int c, float x[size][size])
{
    for(int i = 1; i <= r; i++)
    {
        for(int j = 1; j <= c; j++)
        {
            if(j != c) //途中の列
            {
               printf("%.2f, ", x[i - 1][j - 1]);
            }
            else //端の列
            {
                printf("%.2f\n", x[i - 1][j - 1]);
            }
        }
    }
}

//行列のリセット
void resetMatrix(float x[size][size])
{
    for(int i = 1; i <= size; i++)
    {
        for(int j = 1; j <= size; j++)
        {
            x[i - 1][j - 1] = 0;
        }
    }
}

//行列の取得
void getMatrix(int *rA, int *cA, int *rB, int *cB, float x[size][size], float y[size][size])
{
    int scanID;
    do
    {
        printf("登録する行列の選択\n");
        printf("1:行列A\n");
        printf("2:行列B\n");
        scanf("%d", &scanID);
        system("reset");
    } while (!(1 == scanID || 2 == scanID));
    if(1 == scanID)
    {
        resetMatrix(x);
        do
        {
            printf("行列Aの行数を選択:");
            scanf("%d", rA);
            printf("行列Aの列数を選択:");
            scanf("%d", cA);
            system("reset");
        } while (!(1 <= *rA && *rA <= size && 1 <= *cA && *cA <= size));
        for(int i = 1; i <= *rA; i++)
        {
            for(int j = 1; j <= *cA; j++)
            {
                printf("行列Aの(%d,%d)成分:", i, j);
                scanf("%f", &x[i - 1][j - 1]);
            }
        }
        system("reset");
    }
    else
    {
        resetMatrix(y);
        do
        {
            printf("行列Bの行数を選択:");
            scanf("%d", rB);
            printf("行列Bの列数を選択:");
            scanf("%d", cB);
            system("reset");
        } while (!(1 <= *rB && *rB <= size && 1 <= *cB && *cB <= size));
        for(int i = 1; i <= *rB; i++)
        {
            for(int j = 1; j <= *cB; j++)
            {
                printf("行列Bの(%d,%d)成分:", i, j);
                scanf("%f", &y[i - 1][j - 1]);
            }
        }
        system("reset");
    }
}

//行列の和
void addMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size])
{
    if(rA == rB && cA == cB)
    {
        resetMatrix(z);
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
            {
                z[i - 1][j - 1] = x[i - 1][j - 1] + y[i - 1][j - 1];
            }
        }
        printf("A+B=\n");
        outputMatrix(rA, cA, z);
    }
    else
    {
        printf("行列の和が定義出来ません");
    }
}

//行列の積
void multiMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size])
{
    if(cA == rB)
    {
        resetMatrix(z);
        for(int i = 1; i <= rA; i++)
        {
            for(int j = 1; j <= cB; j++)
            {
                z[i - 1][j - 1] = 0;
                for(int k = 1; k <= rB; k++)
                {
                    z[i - 1][j - 1] += x[i - 1][k - 1] * y[k - 1][j - 1];
                }
            }
        }
        printf("A*B=\n");
        outputMatrix(rA, cB, z);
    }
    else
    {
        printf("行列の積が定義出来ない");
    }
}

//行基本変形・行交換
void P(float x[size], float y[size])
{
    float tmp;
    for(int i = 1; i <= size; i++)
    {
        tmp = x[i - 1];
        x[i - 1] = y[i - 1];
        y[i - 1] = tmp;
    }
}

//行基本変形・行スカラー倍
void Q(float x[size], float c)
{
    for(int i = 1; i <= size; i++)
    {
        x[i - 1] *= c;
    }
}

//行基本変形・行スカラー和
void R(float x[size], float y[size], float c)
{
    for(int i = 1; i <= size; i++)
    {
        x[i - 1] += y[i - 1] * c;
    }
}

//行列の簡約化
void rrefMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size])
{
    int scanID;
    float k;
    int unRank; //階数の最大値よりいくつ小さいか
    int r, c;
    do
    {
        printf("簡約化する行列の選択\n");
        printf("1:行列A\n");
        printf("2:行列B\n");
        scanf("%d", &scanID);
        system("reset");
    } while (!(1 == scanID || 2 == scanID));
    if(1 == scanID)
    {
        r = rA;
        c = cA;
        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                z[i - 1][j - 1] = x[i - 1][j - 1];
            }
        }
    }
    else
    {
        r = rB;
        c = cB;
        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                z[i - 1][j - 1] = y[i - 1][j - 1];
            }
        }
    }
    for(int j = 1; j <= size; j++) //掃き出し法
    {
        for(int i = j + 1 - unRank; i <= size; i++)
        {
            if(0 != z[j - 1 - unRank][j - 1]) break;
            P(z[i - 1], z[j - 1 - unRank]);
        }
        if(0 != z[j - 1 - unRank][j - 1])
        {
            k = 1 / z[j - 1 - unRank][j - 1];
            Q(z[j - 1 - unRank], k);
            for(int i = 1; i <= size; i++)
            {
                if(i != j)
                {
                    k = -z[i - 1][j - 1];
                    R(z[i - 1], z[j - 1 - unRank], k);
                }
            }
        }
        else
        {
            unRank++;
        }
    }
    outputMatrix(r, c, z);
    if(1 == scanID) printf("rankA = %d", size - unRank);
    else printf("rankB = %d", size - unRank);
}

//行列式
int detMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size])
{
    int scanID;
    int n;
    float det = 1;
    float k;
    do
    {
        printf("行列式の選択\n");
        printf("1:detA\n");
        printf("2:detB\n");
        scanf("%d", &scanID);
        system("reset");
    } while (!(1 == scanID || 2 == scanID));
    if(1 == scanID)
    {
        if(rA == cA)
        {
            n = rA;
            for(int i = 1; i <= size; i++)
            {
                for(int j = 1; j <= size; j++)
                {
                    z[i - 1][j - 1] = x[i - 1][j - 1];
                }
            }
        }
        else
        {
            printf("行列式が定義できない");
            return 0;
        }
    }
    else
    {
        if(rB == cB)
        {
            n = rB;
            for(int i = 1; i <= size; i++)
            {
                for(int j = 1; j <= size; j++)
                {
                    z[i - 1][j - 1] = y[i - 1][j - 1];
                }
            }
        }
        else
        {
            printf("行列式が定義できない");
            return 0;
        }
    }
    for(int j = 1; j <= n; j++) //上三角化
    {
        for(int i = j + 1; i <= n; i++)
        {
            if(0 != z[j - 1][j - 1]) break;
            P(z[i - 1], z[j - 1]);
            det *= -1;
        }
        if(0 != z[j - 1][j - 1])
        {
            for(int i = j + 1; i <= n; i++)
            {
                k = -z[i - 1][j - 1] / z[j - 1][j - 1];
                R(z[i - 1], z[j - 1], k);
            }
        }
        else
        { 
            det = 0;
        }
    }
    for(int i = 1; i <= n; i++) //上三角行列の行列式
    {
        det *= z[i - 1][i - 1];
    }
    if(1 == scanID) printf("detA = %.3f", det);
    else printf("detB = %.3f", det);
    return 0;
}

//逆行列
int inverseMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size], float E[size][size])
{
    int scanID, n;
    float k;
    do
    {
        printf("行列の選択\n");
        printf("1:Aインバース\n");
        printf("2:Bインバース\n");
        scanf("%d", &scanID);
        system("reset");
    } while (!(1 == scanID || 2 == scanID));
    if(1 == scanID)
    {
        if(rA == cA)
        {
            n = rA;
            for(int i = 1; i <= size; i++)
            {
                for(int j = 1; j <= size; j++)
                {
                    z[i - 1][j - 1] = x[i - 1][j - 1];
                    if(i == j) E[i - 1][j - 1] = 1;
                    else E[i - 1][j - 1] = 0;
                }
            }
        }
        else
        {
            printf("逆行列が定義できない");
            return 0;
        }
    }
    else
    {
        if(rB == cB)
        {
            n = rB;
            for(int i = 1; i <= size; i++)
            {
                for(int j = 1; j <= size; j++)
                {
                    z[i - 1][j - 1] = y[i - 1][j - 1];
                    if(i == j) E[i - 1][j - 1] = 1;
                    else E[i - 1][j - 1] = 0;
                }
            }
        }
        else
        {
            printf("逆行列が定義できない");
            return 0;
        }
    }
    for(int j = 1; j <= n; j++) //掃き出し法
    {
        for(int i = j + 1; i <= n; i++)
        {
            if(0 != z[j - 1][j - 1]) break;
            P(z[i - 1], z[j - 1]);
            P(E[i - 1], E[j - 1]);
        }
        if(0 != z[j - 1][j - 1])
        {
            k = 1 / z[j - 1][j - 1];
            Q(z[j - 1], k);
            Q(E[j - 1], k);
            for(int i = 1; i <= n; i++)
            {
                if(i != j)
                {  
                    k = -z[i - 1][j - 1];
                    R(z[i - 1], z[j - 1], k);
                    R(E[i - 1], E[j - 1], k);
                }
            }
        }
        else
        {
            printf("正則行列でない");
            return 0;
        }
    }
    outputMatrix(n, n, E);
    return 0;
}

//余因子行列
void adjMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size], float w[size][size])
{
    int scanID, n;
    float k;
    do
    {
        printf("行列の選択\n");
        printf("1:adjA\n");
        printf("2:adjB\n");
        scanf("%d", &scanID);
        system("reset");
    } while (!(1 == scanID || 2 == scanID));
    if(1 == scanID)
    {
        if(rA == cA)
        {
            n = rA;
            resetMatrix(z);
            resetMatrix(w);
            for(int i = 1; i <= n; i++)//余因子の作成
            {
                for(int j = 1; j <= n; j++)
                {
                    int iB = 1, jB = 1;
                    float delta = 1;
                    for(int iA = 1; iA <= n; iA++)//i行j列を除く
                    {
                        if(iA != i)
                        {
                            jB = 1;
                            for(int jA = 1; jA <= n; jA++)
                            {
                                if(jA != j)
                                {
                                    w[iB - 1][jB - 1] = x[iA - 1][jA - 1];
                                    jB++;
                                }
                            }
                            iB++;
                        }
                    }
                    //行列式を作る
                    for(int jA = 1; jA <= n - 1; jA++) //上三角化
                    {
                        for(int iA = jA + 1; iA <= n - 1; iA++)
                        {
                            if(0 != w[jA - 1][jA - 1]) break;
                            P(w[iA - 1], w[jA - 1]);
                            delta *= -1;
                        }
                        if(0 != w[jA - 1][jA - 1])
                        {
                            for(int iA = jA + 1; iA <= n - 1; iA++)
                            {
                                k = -w[iA - 1][jA - 1] / w[jA - 1][jA - 1];
                                R(w[iA - 1], w[jA - 1], k);
                            }
                        }
                        else
                        { 
                            delta = 0;
                        }
                    }
                    for(int iA = 1; iA <= n - 1; iA++) //上三角行列の行列式
                    {
                        delta *= w[iA - 1][iA - 1];
                    }
                    if(0 == (i + j) % 2) z[j - 1][i - 1] = delta;
                    else z[j - 1][i - 1] = -delta;  //結果に代入
                }
            }
        }
        else
        {
            printf("余因子行列が定義できない");
            return;
        }
    }
    else
    {
        if(rB == cB)
        {
            n = rB;
            resetMatrix(z);
            resetMatrix(w);
            for(int i = 1; i <= n; i++)//余因子の作成
            {
                for(int j = 1; j <= n; j++)
                {
                    int iB = 1, jB = 1;
                    float delta = 1;
                    for(int iA = 1; iA <= n; iA++)//i行j列を除く
                    {
                        if(iA != i)
                        {
                            jB = 1;
                            for(int jA = 1; jA <= n; jA++)
                            {
                                if(jA != j)
                                {
                                    w[iB - 1][jB - 1] = y[iA - 1][jA - 1];
                                    jB++;
                                }
                            }
                            iB++;
                        }
                    }
                    //行列式を作る
                    for(int jA = 1; jA <= n - 1; jA++) //上三角化
                    {
                        for(int iA = jA + 1; iA <= n - 1; iA++)
                        {
                            if(0 != w[jA - 1][jA - 1]) break;
                            P(w[iA - 1], w[jA - 1]);
                            delta *= -1;
                        }
                        if(0 != w[jA - 1][jA - 1])
                        {
                            for(int iA = jA + 1; iA <= n - 1; iA++)
                            {
                                k = -w[iA - 1][jA - 1] / w[jA - 1][jA - 1];
                                R(w[iA - 1], w[jA - 1], k);
                            }
                        }
                        else
                        { 
                            delta = 0;
                        }
                    }
                    for(int iA = 1; iA <= n - 1; iA++) //上三角行列の行列式
                    {
                        delta *= w[iA - 1][iA - 1];
                    }
                    if(0 == (i + j) % 2) z[j - 1][i - 1] = delta;
                    else z[j - 1][i - 1] = -delta;  //結果に代入
                }
            }
        }
        else
        {
            printf("余因子行列が定義できない");
            return;
        }
    }
    outputMatrix(n, n, z);
    return;
}

int main()
{
    int menuID;
    float matrixA[size][size], matrixB[size][size], matrixResult[size][size]; //入出力用行列
    float III[size][size]; //単位行列もしくは一時保存用行列
    int rowA, columnA, rowB, columnB; //行列の状態用変数

    resetMatrix(matrixA);//行列の初期化
    resetMatrix(matrixB);

    do
    {
        resetMatrix(matrixResult);//計算用行列の初期化
        resetMatrix(III);

        there:

        printf("\n行列専用演算機\n\n");
        printf("1:行列のリセット/登録\n");
        printf("2:行列の和\n");
        printf("3:行列の積\n");
        printf("4:簡約化\n");
        printf("5:行列式\n");
        printf("6:逆行列\n");
        printf("7:余因子行列\n");
        printf("0:終了\n");
        scanf("%d",&menuID); 
        system("reset");

        if(menuID < 0 || MENUNUMBER < menuID) goto there;
        
        switch (menuID)
        {
            case 1:
                getMatrix(&rowA, &columnA, &rowB, &columnB, matrixA, matrixB);
            break;

            case 2:
                addMatrix(rowA, columnA, rowB, columnB, matrixA, matrixB, matrixResult);
            break;

            case 3:
                multiMatrix(rowA, columnA, rowB, columnB, matrixA, matrixB, matrixResult);
            break;

            case 4:
                rrefMatrix(rowA, columnA, rowB, columnB, matrixA, matrixB, matrixResult);
            break;
            
            case 5:
                detMatrix(rowA, columnA, rowB, columnB, matrixA, matrixB, matrixResult);
            break;

            case 6:
                inverseMatrix(rowA, columnA, rowB, columnB, matrixA, matrixB, matrixResult, III);
            break;

            case 7:
                adjMatrix(rowA, columnA, rowB, columnB, matrixA, matrixB, matrixResult, III);
            break;

            default:
                break;
        }
    } while (0 != menuID);

    return 0;
}