#include <iostream>

//عشان نستخدم راندومايزر
#include <stdlib.h>

//بتجيب الساعة كام دلوقتي والدقيقة كام والثانية كام من الكبيوتر، وبناءا عالوقت بتدينا رقم عشوائي
#include <ctime>

using namespace std;

//الڤاريابل اللي بنستخدمه عشان نحط الحرف بتاع البلاير في المكان الصح
short int playersMove;

//البورد بتاع اللعبة
char fields[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

//ڤاريابلز بنستخدمها في التعامل مع التعادل والفوز
bool Triumph = false, Draw = false;

//الحروف الأساسية لليوزر وللكمبيوتر. بيتغيروا بعدين بناءا على اليوزر عايز يبدأ الأول ولا لا
char user = 'O', computer = 'X';

//دول بنستخدمهم في المود اللي مفهوش كمبيوتر: التاني بيقرر هو دور مين (قيمته بتتغير لما حد يلعب)، والأولاني بيحدد الحرف اللي هيتحط في البورد إكس ولا أو بناءا على قيمة الڤاريابل التاني، والڤاريابل التاني ملوش غير قيمتين عشان بوليان
char NoughtsAndCrosses; bool X_or_O = true;

//أيسم عايزه
bool myTurn = true;


//بيطبع البورد
void printBoard()
{
    cout << "\n-----------------";
    cout << "\n  " << fields[0][0] << "  |  " << fields[0][1] << "  |  " << fields[0][2];
    cout << "\n-----------------";
    cout << "\n  " << fields[1][0] << "  |  " << fields[1][1] << "  |  " << fields[1][2];
    cout << "\n-----------------";
    cout << "\n  " << fields[2][0] << "  |  " << fields[2][1] << "  |  " << fields[2][2];
    cout << "\n-----------------\n";
}


//بياخد رقم من البلاير
void input()
{
m0ve:
    cin >> playersMove;
    
    //بينضف البافر لو في حاجة تتنضف فيه، بتتعامل مع الإيرورز من يوزر متخلف ممكن يدخل رقم ثم حرف
    cin.ignore(10000000000, '\n');
    
    //بتتعامل مع الإيرور وبتخلي البرنامج يشتغل من أول السطر اللي فيه موڤ وبعدين نقطتين فوق بعض عشان البلاير يدخل حاجة تاني
    if (cin.fail())
    {
        cin.clear(); cin.ignore(10000000000, '\n');
        printBoard();
        cout << endl << endl << "You've done a bad. Try again." << endl << endl;
        goto m0ve;
    }
    
    //هنا لو اليوزر دخل رقم بس الرقم أكبر من ٩ أو أصغر من ١
    else if (cin.good() && (playersMove < 1 || playersMove > 9))
    {
        cin.clear();
        printBoard();
        cout << endl << endl << "You've done a bad. Try again." << endl << endl;
        goto m0ve;
    }
}


void takenField()
{
    //لو المكان اللي البلاير لعب فيه متاخد
    if (fields[0][playersMove - 1] == 'X' || fields[0][playersMove - 1] == 'O')
    {
        cin.clear();
        printBoard();
        cout << endl << endl << "This field is more taken than the girl you stare at during the lectures. Try again, dipshit." << endl << endl;
        //خليه يدخل رقم تاني
        input(); takenField();
    }
}


//لو كله تمام وقدرنا ناخد رقم صحيح بين ١ و ٩ من اليوزر، هنوصل هنا
void newBoard()
{
    //بما إننا ممكن نقول:
    //array [0][8]
    //ويبقى كإننا قولنا
    //array [2][2]
    //عشان هو هيشوف الأولانية فهيروح للأراي اللي على بعد ٨ أرقام من:
    //array[0][0]
    //لو كله تمام وخدنا رقم صح، هينقص منه واحد ويحط في الخانة بتاعته الحرف بتاع اليوزر
    //هنا مثلا لو اليوزر دخل ٩، هينقص منها واحد ويبقى أراي صفر تمانية
    fields[0][playersMove - 1] = user;
    printBoard();
}


//كتبتها كتير في الكود، خليتها فانكشن من باب النضافة
void playersTurn()
{
    //مجرد بطبع بورد ورسالة وباخد إنبوت
    newBoard();
    //هنا بستخدم الڤاريابل اللي عمرو كان عايزه مع إنه ملوش لازمة
    myTurn = false;
    cout << endl << endl << "Your move." << endl << endl;
    input(); takenField(); newBoard();
    myTurn = true;
}


//دي اللي بنستخدمها في الموڤز بتاعة الكمبيوتر. هي فيها پاراميتير، وفيها رسالة بتقول إنه دور الكمبيوتر. الپاراميتير ده رقم هنحطه بين القوسين كل مرة نستخدم الفانكشن دي، فهينقص منه واحد، وبعدين يحط حرف الكمبيوتر بنفس الطريقة بتاعة حرف اليوزر
void computersMove(short int myMove)
{
    cout << endl << endl << "Computer's move." << endl << endl;
    fields[0][myMove - 1] = computer;     myTurn = false;
}


void victory()
{
    for (short int i = 0; i < 3; i++)
    {
        //دي بتعدي عالصفوف كلها وبتشوف فيهم ٣ زي بعض ولا لا
        if (fields [i][0] == fields [i][1] && fields[i][1] == fields[i][2])
        {Triumph = true;}
        //عواميد
        if (fields [0][i] == fields [1][i] && fields[1][i] == fields[2][i])
        {Triumph = true;}
    }
    //دياجونالز
    if ((fields[0][0] == fields[1][1] && fields[1][1] == fields[2][2]) ||
        (fields[0][2] == fields[1][1] && fields[1][1] == fields[2][0]))
    {Triumph = true;}
}

void tie()
{
    //بتعدي على كل حاجة ولو البورد مليان يبقى draw صح
    
    short int count = 0;
    
    for (short int j = 0; j <= 8; j++)
    {
        if (fields[0][j] == 'X' || fields[0][j] == 'O')
        {count++;}
    }
    if (count == 9)
    {Draw = true;}
}

//فانكشن عمرو اللي بتحط إكس في مكان لو ممكن نكسب منه، أو لو اليوزر ممكن يكسب بتحط إكس في المكان اللي هيقفل عليه
bool offense()
{
    if (myTurn == true)
    {
    for (int x = 0; x < 3; x++)
    {
        {
            for (int y = 0; y < 3; y++)
            {
                //بتعدي عالصفوف. بتشوف لو في مكان فاضي وجنبه مكانين الكمبيوتر واخدهم، ولو في، بتحط اكس في المكان الفاضي ده
                //هي بتشوف المكان اللي جنب المكان الفاضي من عالشمال، والمكان اللي جنبه من عاليمين، والمكانين اللي جنبه من عاليمين، والمكانين اللي جنبه من عالشمال
                if ((fields[x][y] != 'X' && fields[x][y] != 'O') && ((fields[x][y+1] == computer && fields[x][y-1] == computer && y + 1 <= 2 && y - 1 >= 0) || (fields[x][y+2] == computer && fields[x][y+1] == computer && y + 2 <= 2) || (fields[x][y-2] == computer && fields[x][y-1] == computer && y - 2 >= 0)))
                {
                    cout << endl << endl << "Computer's move." << endl << endl;
                    fields[x][y] = computer;     myTurn = false;
                    //الحتت دي أنا حاططها عشان في غلطات في الفانكشن، فبتساعدني أعرف بالظبط الغلطة جاية من أنهي إحتمال. تتشال لما الفانكشن تستقر ١٠٠٪
                    cout << x << "\t" << y << "\tIF NUMBER ONE\n\n";
                    newBoard(); return true;
                }
                //نفس الكلام اللي فوق بس عالعواميد
                if ((fields[y][x] != 'X' && fields[y][x] != 'O') && ((fields[y+1][x] == computer && fields[y-1][x] == computer && y + 1 <= 2 && y - 1 >= 0) || (fields[y+2][x] == computer && fields[y+1][x] == computer && y + 2 <= 2) || (fields[y-2][x] == computer && fields[y-1][x] == computer && y - 2 >= 0)))
                {
                    cout << endl << endl << "Computer's move." << endl << endl;
                    fields[y][x] = computer;     myTurn = false;;
                    cout << y << "\t" << x << "\tIF NUMBER TWO\n\n";
                    newBoard(); return true;
                }
            }
        }
        //بتعدي عالدياجونال اللي هو فوق شمال لتحت يمين
        if (((fields[x][x] != 'X' && fields[x][x] != 'O') && ((fields[x+1][x+1] == computer && fields[x+2][x+2] == computer && x + 2 <= 2) || (fields[x+1][x+1] == computer && fields[x-1][x-1] == computer && x + 1 <= 2 && x - 1 >= 0) || (fields[x-1][x-1] == computer && fields[x-2][x-2] == computer && x - 2 >= 0))))
        {
            cout << endl << endl << "Computer's move." << endl << endl;
            fields[x][x] = computer;     myTurn = false;
            cout << x << "\t" << x << "\tIF NUMBER THREE\n\n";
            newBoard(); return true;
        }
    }
    
    //دي كده كلها بتعدي عالدياجونال التاني، اللي هو معقد اكتر شوية
    for (int i = 0; i < 3; i++)
        {
            for (int j = 2; j >= 0; j--)
            {
                if ((fields[i][j] != 'X' && fields[i][j] != 'O') &&
                    ((fields[i+1][j-1] == computer && (i + 1 <= 2 && j - 1 >= 0) &&
                      (fields[i+2][j-2] == computer && (i + 2 <= 2 && j - 2 >= 0))) ||
                     
                     
                     (fields[i+1][j-1] == computer && (i + 1 <= 2 && j - 1 >= 0) &&
                      (fields[i-1][j+1] == computer && (i - 1 >= 0 && j + 1 <= 2))) ||
                     
                     
                     (fields[i+1][j-1] == computer && (i + 1 <= 2 && j - 1 >= 0) &&
                      (fields[i-2][j+2] == computer && (j + 2 <= 2 && i - 2 >= 0)))))
                {
                    cout << endl << endl << "Computer's move." << endl << endl;
                    fields[i][j] = computer;     myTurn = false;
                    cout << i << "\t" << j << "\tIF NUMBER FOUR\n\n";
                    newBoard(); return true;
                }
            }
        }
    
    
    //لو كل اللي فوق اشتغل ومفيش أي إحتمال إتحقق ومفيش أي فوز حصل، هنوصل للحتة دي
    //دي بتعدي عالبورد كله وتشوف في كام خانة ملعوب فيها. لو ٨ ملعوب فيهم وناقص خانة للتعادل، هتحط حرف الكمبيوتر في الخانة دي
    short int count = 0;
    
    for (short int j = 0; j <= 8; j++)
    {
        if (fields[0][j] == 'X' || fields[0][j] == 'O')
            
        {count++;}
    }
    
    if (count == 8)
    {
        for (short int j = 0; j <= 8; j++)
        {
            if (fields[0][j] != 'X' && fields[0][j] != 'O')
            {
                fields[0][j] = computer;     myTurn = false;
                cout << 0 << "\t" << j << "\tIF NUMBER FIVE\n\n";
                newBoard(); return true;
            }
        }
    }
    }
    return 0;
}

bool defense()
{
    if (myTurn == true) {
    for (int x = 0; x < 3; x++)
    {
        {
            for (int y = 0; y < 3; y++)
            {
                //بتعدي عالصفوف. بتشوف لو في مكان فاضي وجنبه مكانين الكمبيوتر واخدهم، ولو في، بتحط اكس في المكان الفاضي ده
                //هي بتشوف المكان اللي جنب المكان الفاضي من عالشمال، والمكان اللي جنبه من عاليمين، والمكانين اللي جنبه من عاليمين، والمكانين اللي جنبه من عالشمال
                if ((fields[x][y] != 'X' && fields[x][y] != 'O') && ((fields[x][y+1] == user && fields[x][y-1] == user && y + 1 <= 2 && y - 1 >= 0) || (fields[x][y+2] == user && fields[x][y+1] == user && y + 2 <= 2) || (fields[x][y-2] == user && fields[x][y-1] == user && y - 2 >= 0)))
                {
                    cout << endl << endl << "Computer's move." << endl << endl;
                    fields[x][y] = computer;     myTurn = false;;
                    //الحتت دي أنا حاططها عشان في غلطات في الفانكشن، فبتساعدني أعرف بالظبط الغلطة جاية من أنهي إحتمال. تتشال لما الفانكشن تستقر ١٠٠٪
                    cout << x << "\t" << y << "\tIF NUMBER ONE\n\n";
                    newBoard(); return true;
                }
                //نفس الكلام اللي فوق بس عالعواميد
                if ((fields[y][x] != 'X' && fields[y][x] != 'O') && ((fields[y+1][x] == user && fields[y-1][x] == user && y + 1 <= 2 && y - 1 >= 0) || (fields[y+2][x] == user && fields[y+1][x] == user && y + 2 <= 2) || (fields[y-2][x] == user && fields[y-1][x] == user && y - 2 >= 0)))
                {
                    cout << endl << endl << "Computer's move." << endl << endl;
                    fields[y][x] = computer;     myTurn = false;
                    cout << y << "\t" << x << "\tIF NUMBER TWO\n\n";
                    newBoard(); return true;
                }
            }
        }
        //بتعدي عالدياجونال اللي هو فوق شمال لتحت يمين
        if (((fields[x][x] != 'X' && fields[x][x] != 'O') && ((fields[x+1][x+1] == user && fields[x+2][x+2] == user && x + 2 <= 2) || (fields[x+1][x+1] == user && fields[x-1][x-1] == user && x + 1 <= 2 && x - 1 >= 0) || (fields[x-1][x-1] == user && fields[x-2][x-2] == user && x - 2 >= 0))))
        {
            cout << endl << endl << "Computer's move." << endl << endl;
            fields[x][x] = computer;     myTurn = false;;
            cout << x << "\t" << x << "\tIF NUMBER THREE\n\n";
            newBoard(); return true;
        }
    }
    
    //دي كده كلها بتعدي عالدياجونال التاني، اللي هو معقد اكتر شوية
    for (int i = 0; i < 3; i++)
    {
        for (int j = 2; j >= 0; j--)
        {
            if ((fields[i][j] != 'X' && fields[i][j] != 'O') &&
                ((fields[i+1][j-1] == user && (i + 1 <= 2 && j - 1 >= 0) &&
                  (fields[i+2][j-2] == user && (i + 2 <= 2 && j - 2 >= 0))) ||
                 
                 
                 (fields[i+1][j-1] == user && (i + 1 <= 2 && j - 1 >= 0) &&
                  (fields[i-1][j+1] == user && (i - 1 >= 0 && j + 1 <= 2))) ||
                 
                 
                 (fields[i+1][j-1] == user && (i + 1 <= 2 && j - 1 >= 0) &&
                  (fields[i-2][j+2] == user && (j + 2 <= 2 && i - 2 >= 0)))))
            {
                cout << endl << endl << "Computer's move." << endl << endl;
                fields[i][j] = computer;     myTurn = false;
                cout << i << "\t" << j << "\tIF NUMBER FOUR\n\n";
                newBoard(); return true;
            }
        }
    }
    }
    return 0;
}


//كلنا حضرنا الحتة دي أظن وشاركنا فيها
//بالمناسبة أنا كنت عايز أكود AI بيجرب حاجات كتير جدا ويختار أحسن مكان بناءا عن تجاربه، بس أيسم شخرلي
void ComputerMode()
{
    //البتاع هيجيب رقم عشوائي، من صفر لتلاتة

//لو الرقم صفر
    short int one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9;
    
    //srand((short int) time(NULL));
    //خليها كده دلوقتي عشان خاطر التيستينج بس، لما اللعبة تكون مستقرة ومفهاش أي غلطات خلي السطر اللي قبل ده مش كومنت واللي جاي مش كومنت بردو وشيل اللي بعده خالص
    //short int start = (rand() % 4);
    short int start = 0;
    
    //بنشقلب البورد ٣ مرات
    if (start == 1)
    {
        one = 7; two = 8; three = 9; four = 4; six = 6; seven = 1; eight = 2; nine = 3;
    }
    else if (start == 2)
    {
        one = 3; two = 2; three = 1; four = 6; six = 4; seven = 9; eight = 8; nine = 7;
    }
    else if (start == 3)
    {
        one = 9; two = 8; three = 7; four = 6; six = 4; seven = 3; eight = 2; nine = 1;
    }
    
    
    //هنا كل اللي بيحصل إننا بنلعب، وبعدين بنحط الفانكشن اللي بتخلي البلاير يلعب، وبعدها بنحط إحتمالات لرده وبنرد عالرد
    //هنا مش بنكتب كل الخطوات والإحتمالات، بنكتب اللي محتاجين نكتبه عشان نوصل لمكان نكسب منه، وبعدها الفانكشن بتنتهي والفانكشن بتاعة عمرو هي اللي بتكسبنا
    
    computersMove(one);
    playersTurn();
    
    //الأرقام في الكومنتات دي قديمة من أيام ما كانت الفانكشن دي متتقريش عشان كلها أرايز. ملهاش لازمة دلوقتي
    
    if (playersMove == nine)
    {
        computersMove(three); //3
        playersTurn();

        if (playersMove == two)
        {
            computersMove(seven); //7
            playersTurn();
        }
    }
    
    else if (playersMove == seven)
    {
        computersMove(nine); //9
        playersTurn();
        
        if (playersMove == five)
        {
            computersMove(three); //3
            playersTurn();
        }
    }
    
    else if (playersMove == three)
    {
        computersMove(nine); //9
        playersTurn();
        
        if (playersMove == five)
        {
            computersMove(seven); //7
            playersTurn();
        }
    }
    
    
    else if (playersMove == two)
    {
        computersMove(seven); //7
        playersTurn();
        
        if (playersMove == four)
        {
            computersMove(nine); //9
            playersTurn();
        }
    }
    
    
    else if (playersMove == four)
    {
        computersMove(three); //3
        playersTurn();
        
        if (playersMove == two)
        {
            computersMove(five); //5
            playersTurn();
        }
    }
    
    
    else if (playersMove == six || playersMove == eight)
    {
        computersMove(seven); //7
        playersTurn();
        
        if (playersMove == four)
        {
            computersMove(five); //5
            playersTurn();
        }
    }
    
    
    else if (playersMove == five)
    {
        computersMove(nine); //9
        playersTurn();
        defense();
    }
}


//في حالة إنه هيلاعب صديق
void twoPlayersMode()
{
    //إطلع فوق خالص وشوف الڤاريابلز اللي أنا عاملها للتو بلاير مود، عشان هما الحاجتين الأساسيين هنا
    //لو البوليان صحيح، الڤاريابل هتبقى قيمته إكس؛ لو غلط، هتبقى أو. البوليان صحيح في الأول
    if (X_or_O)
    {
        NoughtsAndCrosses = 'X';
        cout << endl << endl << "Player one's move." << endl << endl;
    }
    else
    {
        NoughtsAndCrosses = 'O';
        cout << endl << endl << "Player two's move." << endl << endl;
    }
    
    
    //باخد إنبوت من واحد منهم، وبعدها...
    input(); takenField();
    
    //بعكس قيمة البوليان. لو هو صح، هيبقى غلط. فبالتالي لما ننرجع للفانكشن دي تاني، هيعكس قيمته تاني، فهتتحول من غلط لصح، وهكذا... وعكس القيمة بيغير هو دور مين
    X_or_O = !X_or_O;

    //بيتحط حرف اليوزر في الخانة اللي خدناها منه
    fields[0][playersMove - 1] = NoughtsAndCrosses;
    
    printBoard();
}

//حاولت أحط الحتة دي فوق مشتغلتش صج فخليتها فانكشن لوحدها، جربت تاني دلوقتي إشتغلت
/*
void HAHAFUCKYOUCPLUSPLUS()
{
    X_or_O = !X_or_O;
    
    fields[0][playersMove - 1] = NoughtsAndCrosses;
    printBoard();
}
*/


//أكتر حاجة محتاجة تنضيف
int main(){
    
    short int selection;
    
    cout << "Hello, friend.\n\n";
idiot:
    cout << "Select your opponent:\n1- Me\n2- A friend\n\n";
    cin >> selection;
    cin.ignore(10000000000, '\n');
    
    if (cin.fail())
    {
        cout << "Try again." << endl << endl;
        cin.clear(); cin.ignore(10000000000, '\n');;
        goto idiot;
    }
    
    
    if (selection == 1)
{
        cout << endl << "Would you like to go first? Enter 'y' or 'n' to answer." << endl;
        char answer;
        cin >> answer;
        if (answer == 'n' || answer == 'N')
    {
            user = 'O'; computer = 'X';
        
        printBoard();
    heh:
        ComputerMode();
        offense();
        victory();
        tie();
        
        if (Triumph) {
            cout << endl << "I won." << endl;
            return Triumph;
        }
        
        if (Draw)
        {
            cout << endl << "You're a worthy opponent." << endl;
            return Draw;
        }
    }
        else if (answer == 'Y' || answer == 'y')
        {
            user = 'X'; computer = 'O';
            cout << endl << "I haven't programmed that path yet." << endl;
        }
        else
        {
            cout << endl << "The world would be a lovely place if you choked on sarin gas." << endl;
        }
}
    
    else if (selection == 2)
    {
        
        printBoard();
    again:
        twoPlayersMode();
        //HAHAFUCKYOUCPLUSPLUS();
        victory();
        tie();
        if (Triumph)
        {
            cout << endl << "VICTORY!!" << endl;
            return Triumph;
        }
        
        if (Draw)
        {
            cout << endl << "YOU BOTH SUCK AT THIS!" << endl;
            return Draw;
        }
        goto again;
    }
    
    else if (selection < 1 || selection > 2)
    {
        cout << "Very funny I forgot to laugh.\n\n"; goto idiot;
    }
}
