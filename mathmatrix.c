#include<stdio.h>
#include<stdlib.h>
#define MENUNUMBER 7
#define size 5

//コンソールクリア用マクロ
#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif


//行列の出力
void outputMatrix(int r, int c, float x[size][size])
{
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            printf("%8.3f", x[i][j]);
            if (j < c - 1) printf(", ");
            else printf("\n");
        }
    }
}


//行列のリセット
void resetMatrix(float x[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            x[i][j] = 0;
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
        system(CLEAR_CMD);
    } while (!(1 == scanID || 2 == scanID));

    //行列Aの取得
    if(1 == scanID)
    {
        resetMatrix(x);

        //行列のサイズ選択
        do
        {
            printf("行列Aの行数を選択(1~%d):", size);
            scanf("%d", rA);
            printf("行列Aの列数を選択(1~%d):", size);
            scanf("%d", cA);
            system(CLEAR_CMD);
        } while (!(1 <= *rA && *rA <= size && 1 <= *cA && *cA <= size));

        //行列の登録
        for(int i = 0; i < *rA; i++)
        {
            for(int j = 0; j < *cA; j++)
            {
                printf("行列Aの(%d,%d)成分:", i + 1, j + 1);
                scanf("%f", &x[i][j]);
            }
        }

        system(CLEAR_CMD);
    }

    //行列Bの取得
    else
    {
        resetMatrix(y);

        //行列のサイズ選択
        do
        {
            printf("行列Bの行数を選択:");
            scanf("%d", rB);
            printf("行列Bの列数を選択:");
            scanf("%d", cB);
            system(CLEAR_CMD);
        } while (!(1 <= *rB && *rB <= size && 1 <= *cB && *cB <= size));

        //行列の登録
        for(int i = 0; i < *rB; i++)
        {
            for(int j = 0; j < *cB; j++)
            {
                printf("行列Bの(%d,%d)成分:", i + 1, j + 1);
                scanf("%f", &y[i][j]);
            }
        }

        system(CLEAR_CMD);
    }
}


//行列の和
void addMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size])
{
    if(rA == rB && cA == cB)
    {
        resetMatrix(z);

        //加算
        for (int i = 0; i < rA; i++)
        {
            for (int j = 0; j < cA; j++)
            {
                z[i][j] = x[i][j] + y[i][j];
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

        for(int i = 0; i < rA; i++)
        {
            for(int j = 0; j < cB; j++)
            {
                z[i][j] = 0;
                for(int k = 0; k < rB; k++)
                {
                    z[i][j] += x[i][k] * y[k][j];
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


//行基本変形・xとyの行交換
void P(float x[size], float y[size])
{
    float tmp;
    for(int i = 0; i < size; i++)
    {
        tmp = x[i];
        x[i] = y[i];
        y[i] = tmp;
    }
}

//行基本変形・xをcで行スカラー倍
void Q(float x[size], float c)
{
    for(int i = 0; i < size; i++)
    {
        x[i] *= c;
    }
}

//行基本変形・xにyをc倍したものを行スカラー和
void R(float x[size], float y[size], float c)
{
    for(int i = 0; i < size; i++)
    {
        x[i] += y[i] * c;
    }
}


//行列の簡約化
void rrefMatrix(int rA, int cA, int rB, int cB, float x[size][size], float y[size][size], float z[size][size])
{
    int scanID;
    float k;
    int unRank = 0; //階数の最大値よりいくつ小さいか
    int r, c;
    int rank;

    do
    {
        printf("簡約化する行列の選択\n");
        printf("1:行列A\n");
        printf("2:行列B\n");
        scanf("%d", &scanID);
        system(CLEAR_CMD);
    } while (!(1 == scanID || 2 == scanID));

    //行列を計算用行列にコピー
    if(1 == scanID)
    {
        r = rA;
        c = cA;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                z[i][j] = x[i][j];
            }
        }
    }
    else
    {
        r = rB;
        c = cB;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j <size; j++)
            {
                z[i][j] = y[i][j];
            }
        }
    }

    /*******掃き出し法開始********/
    for(int j = 0; j < c; j++) //列毎に処理
    {
        int pivotRow = j - unRank; //ピボット候補の行の端

        // ピボットのある行の探索
        int found = -1; //ピボットのある行保存用
        for (int i = pivotRow; i < r; i++)
        {
            if (0 != z[i][j])
            {
                found = i;
                break;
            }
        }

        // ピボットが見つからなければランク減少し次の列へ
        if (-1 == found)
        {
            unRank++;
            continue;
        }

        //ピボットのある行を先頭へ持っていく
        P(z[pivotRow], z[found]);

        //ピボットを１にする
        k = 1 / z[pivotRow][j];
        Q(z[pivotRow], k);

        //他の行のピボットがある列を0にする
        for(int i = 0; i < r; i++)
        {
            if(i != pivotRow)
            {
                k = -z[i][j];
                R(z[i], z[pivotRow], k);
            }
        }
        rank = pivotRow + 1;
    }
    /*******掃き出し法終了********/

    outputMatrix(r, c, z);
    if(1 == scanID) printf("rankA = %d\n", rank);
    else printf("rankB = %d\n", rank);
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
        system(CLEAR_CMD);
    } while (!(1 == scanID || 2 == scanID));

    //行列を計算用行列にコピー
    if(1 == scanID)
    {
        if(rA == cA)
        {
            n = rA;
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    z[i][j] = x[i][j];
                }
            }
        }
        else
        {
            printf("行列式が定義できない\n");
            return 0;
        }
    }
    else
    {
        if(rB == cB)
        {
            n = rB;
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    z[i][j] = y[i][j];
                }
            }
        }
        else
        {
            printf("行列式が定義できない");
            return 0;
        }
    }

    /*******ガウスの消去法開始********/
    for(int j = 0; j < n; j++) //上三角化
    {
        if(0 == z[j][j]) //0でないピボットを探す
        {
            int found = -1;
            for(int i = j + 1; i < n; i++)
            {
                if(0 != z[i][j])
                {
                    P(z[i], z[j]);
                    det *= -1;
                    found = i;
                    break;
                }
            }
            if(-1 == found)
            {
                det = 0;
                break;
            }
        }
        for(int i = j + 1; i < n; i++)
        {
            k = -z[i][j] / z[j][j];
            R(z[i], z[j], k);
        }
    }
    /*******ガウスの消去法終了********/

    //行列式の計算
    if(0 != det)
    {
        for(int i = 0; i < n; i++)
        {
            det *= z[i][i];
        }
    }

    if(1 == scanID) printf("detA = %.3f\n", det);
    else printf("detB = %.3f\n", det);
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
        system(CLEAR_CMD);
    } while (!(1 == scanID || 2 == scanID));

    //行列を計算用行列にコピー
    if(1 == scanID)
    {
        if(rA == cA)
        {
            n = rA;
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    z[i][j] = x[i][j];
                    if(i == j) E[i][j] = 1;
                    else E[i][j] = 0;
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
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < size; j++)
                {
                    z[i][j] = y[i][j];
                    if(i == j) E[i][j] = 1;
                    else E[i][j] = 0;
                }
            }
        }
        else
        {
            printf("逆行列が定義できない");
            return 0;
        }
    }


    /*******掃き出し法開始********/
    for(int j = 0; j < n; j++) //列毎に処理
    {
        // ピボットのある行の探索
        int found = -1; //ピボットのある行保存用
        for (int i = j; i < n; i++)
        {
            if (0 != z[i][j])
            {
                found = i;
                break;
            }
        }

        // ピボットが見つからなければ正則でない
        if (-1 == found)
        {
            printf("正則行列でない\n");
            return 0;
        }

        //ピボットを１にする
        k = 1 / z[j][j];
        Q(z[j], k);
        Q(E[j], k);

        //他の行のピボットがある列を0にする
        for(int i = 0; i < n; i++)
        {
            if(i != j)
            {
                k = -z[i][j];
                R(z[i], z[j], k);
                R(E[i], E[j], k);
            }
        }
    }
    /*******掃き出し法終了********/

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
        system(CLEAR_CMD);
    } while (!(1 == scanID || 2 == scanID));

    if(1 == scanID)
    {
        if(rA == cA)
        {
            n = rA;
            resetMatrix(z);
            resetMatrix(w);
            for(int i = 0; i < n; i++)//余因子の作成
            {
                for(int j = 0; j < n; j++)
                {
                    int iB = 0, jB = 0;
                    float delta = 1;
                    for(int iA = 0; iA < n; iA++)//i行j列を除く
                    {
                        if(iA != i)
                        {
                            jB = 0;
                            for(int jA = 0; jA < n; jA++)
                            {
                                if(jA != j)
                                {
                                    w[iB][jB] = x[iA][jA];
                                    jB++;
                                }
                            }
                            iB++;
                        }
                    }
                    /*******行列式開始********/
                    for(int jA = 0; jA < n - 1; jA++) //上三角化
                    {
                        if(0 == w[jA][jA]) //0でないピボットを探す
                        {
                            int found = -1;
                            for(int iA = jA + 1; iA < n - 1; iA++)
                            {
                                if(0 != w[iA][jA])
                                {
                                    P(w[iA], w[jA]);
                                    delta *= -1;
                                    found = iA;
                                    break;
                                }
                            }
                            if(-1 == found)
                            {
                                delta = 0;
                                break;
                            }
                        }
                        for(int iA = jA + 1; iA < n - 1; iA++)
                        {
                            k = -w[iA][jA] / w[jA][jA];
                            R(w[iA], w[jA], k);
                        }
                    }
                    if(0 != delta)
                    {
                        for(int i = 0; i < n - 1; i++)
                        {
                            delta *= w[i][i];
                        }
                    }
                    /*******行列式終了********/
                    //結果保存用行列に代入
                    if(0 == (i + j) % 2) z[j][i] = delta;
                    else z[j][i] = -delta;  //結果に代入
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
            for(int i = 0; i < n; i++)//余因子の作成
            {
                for(int j = 0; j < n; j++)
                {
                    int iB = 0, jB = 0;
                    float delta = 1;
                    for(int iA = 0; iA < n; iA++)//i行j列を除く
                    {
                        if(iA != i)
                        {
                            jB = 0;
                            for(int jA = 0; jA < n; jA++)
                            {
                                if(jA != j)
                                {
                                    w[iB][jB] = y[iA][jA];
                                    jB++;
                                }
                            }
                            iB++;
                        }
                    }
                    /*******行列式開始********/
                    for(int jA = 0; jA < n - 1; jA++) //上三角化
                    {
                        if(0 == w[jA][jA]) //0でないピボットを探す
                        {
                            int found = -1;
                            for(int iA = jA + 1; iA < n - 1; iA++)
                            {
                                if(0 != w[iA][jA])
                                {
                                    P(w[iA], w[jA]);
                                    delta *= -1;
                                    found = iA;
                                    break;
                                }
                            }
                            if(-1 == found)
                            {
                                delta = 0;
                                break;
                            }
                        }
                        for(int iA = jA + 1; iA < n - 1; iA++)
                        {
                            k = -w[iA][jA] / w[jA][jA];
                            R(w[iA], w[jA], k);
                        }
                    }
                    if(0 != delta)
                    {
                        for(int i = 0; i < n - 1; i++)
                        {
                            delta *= w[i][i];
                        }
                    }
                    /*******行列式終了********/
                    if(0 == (i + j) % 2) z[j][i] = delta;
                    else z[j][i] = -delta;  //結果に代入
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