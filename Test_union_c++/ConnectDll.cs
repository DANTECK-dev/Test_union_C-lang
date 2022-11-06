using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConnectDLL
{
    // структура для описания состояния физ. памяти
    struct PHYS_MEMORY_BLOCK
    {
        int nStart; // начало блока в оперативной памяти
        int nLength; // длина блока
        int nProcess; // номер процесса (0-99), которому выделен блок (255 - система)
    };
    enum PROCESS_STATUS
    {
        NotExist = 0,
        Execute = 1,
        Ready = 2,
        Wait = 3
    };
    enum MEMORY_OPERATION
    {
        MemoryRead = 0,
        MemoryWrite = 1
    };
    static class DLL
    {
        [DllImport("MathLibrary.dll")]
        /*
            1. Аппаратные функции - данные функции реализованы с модели
            операционной системы, их использование обязательно при обращении к
            виртуальной машине :
        */

        // - 1.1 получить размер оперативной памяти(в байтах);
        internal static extern ulong GetMemorySize();

        [DllImport("MathLibrary.dll")]
        //1.2 - получить размер страницы(в байтах);
        internal static extern int GetPageSize();

        [DllImport("MathLibrary.dll")]
        //1.3 - получить размер диска(в байтах);
        internal static extern ulong GetDiskSize();

        [DllImport("MathLibrary.dll")]
        //1.4 - получить размер кластера(в байтах);
        internal static extern ulong GetSectorSize();

        [DllImport("MathLibrary.dll")]
        //1.5  -записать строку в лог(не более 40К за 500 мс);
        internal static extern void AddLog(char[] s, int size);

        [DllImport("MathLibrary.dll")]
        //1.6  -считать байт из памяти по физ.адресу;
        internal static extern Byte ReadMemoryByte(int memPhysAdress);

        [DllImport("MathLibrary.dll")]
        //1.7 - записать байт в память по физ.адресу;
        internal static extern void WriteMemoryByte(int memPhysAdress, Byte value);

        [DllImport("MathLibrary.dll")]
        //1.8 - считать из памяти по указанному физ.адресу несколько байт
        //(memPhysAdress - адрес, с которого надо считывать данные, lpBuffer -
        //буфер, в который необходимо перенести указанные данные, count -
        //количество считываемых байт);
        internal static extern void ReadMemory(int memPhysAdress, Byte[] lpBuffer, int count);

        [DllImport("MathLibrary.dll")]
        //1.9  - записать в памяти из указанного буфера несколько байт
        //(memPhysAdress - адрес, по которому происходит запись, lpBuffer -
        //буфер, из которого переносятся данные, count - количество байт);
        internal static extern void WriteMemory(int memPhysAdress, Byte[] lpBuffer, int count);

        [DllImport("MathLibrary.dll")]
        //1.10  - считать кластер
        //с диска(внимание, функция блокирующая), параметры: memAdress -
        //адрес в оперативной памяти, начиная с которого необходимо
        //поместить содержимое кластера, nSector - номер кластера диска, с
        //которого небходимо считать данные;
        internal static extern void ReadDisk(int memAdress, int nSector);

        [DllImport("MathLibrary.dll")]
        //1.11  - записать
        //кластер с диска(внимание, функция блокирующая), параметры:
        //memAdress - адрес в оперативной памяти, начиная с которого данные
        //записываются в кластер, nSector - номер кластера диска, в который
        //записываются данные.
        internal static extern void WriteDisk(int memAdress, int nSector);

        [DllImport("MathLibrary.dll")]

        /*
            2. Функции ОС - прототипы функций, которые необходимо реализовать
            согласно варианту :
        */

        //2.1  - запуск подсистем управления, начальная
        //инициализация подсистем;
        internal static extern void Start();

        [DllImport("MathLibrary.dll")]
        //2.2 - остановка подсистем управления, остановка
        //подсистем управления.
        internal static extern void Stop();

        [DllImport("MathLibrary.dll")]

        /*
            3. Функции ОС, информационные - прототипы функций, которые
            необходимо реализовать согласно варианту :
        */

        //3.1 - получить информацию о процессах в системе,
        //размер буфера = 100, фактически является "планировщиком"
        //процессов
        internal static extern void GetProcessStatus(Byte[] lpProcStatusBuffer, double[] lpProcData);

        [DllImport("MathLibrary.dll")]
        //3.2  - получить количество блоков;
        internal static extern int GetPhysMemoryBlockCount();

        [DllImport("MathLibrary.dll")]
        //3.3  - получить описание
        //блоков, lpBlockList - список описания блоков;
        internal static extern void GetPhysMemoryBlockList(PHYS_MEMORY_BLOCK[] lpBlockList);

        [DllImport("MathLibrary.dll")]
        //3.4  - получить
        //информацию о состоянии диска(посекторно), 0 - свободный
        //сектор, 1 - 100 - сектор принадлежит файлу(номер совпадает с
        //номером в каталоге), 255 - зарезервировано системой;
        internal static extern void GetDiskStatus(Byte[] lpStatusBuffer);

        [DllImport("MathLibrary.dll")]
        //3.5  - получить каталог, файлов на диске не
        //более 100 (индексы с 1 по 100 включительно), lpFileNames - имена
        //файлов, lpFirstSectors - номера первых кластеров, lpSizes - размеры
        //файлов;
        internal static extern void GetDiskCatalog(char[][] lpFileNames, int[] lpFirstSectors, int[] lpSizes);
        
        [DllImport("MathLibrary.dll")]
        //3.6 - создать процесс, nData -
        //дополнительные параметры для процесса(зависит от алгоритма
        //планирования), 1. Гарантированное планирование - номер
        //пользователя от имени которого запущен процесс, 2. SJF с
        //предсказанием - не используется, 3. Вытесняющий SJF - полное
        //время выполнения процесса, 4. Приоритетное планирование с
        //абсолютным приоритетом - номер приоритета, 5. Многоуровневая
        //очередь(2 уровня: высокий приоритет – Round robin, низкий
        //приоритет – FCFS) - номер приоритета, функция должна вернуть
        //номер для созданного процесса;
        internal static extern int osCreateProcess(int nData);

        [DllImport("MathLibrary.dll")]
        //3.7  - удалить процесс с указанным номером
        internal static extern void osDeleteProcess(int nProcess);

        [DllImport("MathLibrary.dll")]
        /*
            4. Функции ОС, управление памятью - прототипы функций, которые
            необходимо реализовать согласно варианту :
        */

        //4.1  - создать адресное пространство для
        //указанного процесса, nProcess - номер процесса для которого
        //создается адресное пространство, bBlockCount - количество блоков
        //адресного пространства, для страничного распределения
        //bBlockCount всегда равен 1, для сегментного и сегментностраничного распределения - количество сегментов, lpBlockLength
        //- длины блоков аресного пространства;
        internal static extern void osMakeAddressSpace(int nProcess, int bBlockCount, int[] lpBlockLength);
        
        [DllImport("MathLibrary.dll")]
        //4.2  - выполнить трансляцию адреса, nProcess - номер
        //процесса, в адресном пространстве которого выполняется
        //преобразование, nVirtualAdress - виртуальный адрес, по которому
        //пытаемся произвести обращение, nOperationType - выполняемая
        //операция при доступе к ячейке памяти(MemoryRead или
        //MemoryWrite), функция должна вернуть номер физ.ячейки или - 1
        //если необходимая часть адресного пространства отсутствует в
        //оперативной памяти;
        internal static extern int osTranslateAddress(int nProcess, int nVirtualAdress, int nOperationType);
        
        [DllImport("MathLibrary.dll")]
        //4.3  - выполнить трансляцию адреса,
        //nProcess - номер процесса, в адресном пространстве которого
        //выполняется преобразование, nSegment - номер сегмента, к
        //которому пытаемся произвести обращение, nOffset - смещение в
        //сегменте, nOperationType - выполняемая операция при доступе к
        //ячейке памяти(MemoryRead или MemoryWrite), функция должна
        //вернуть номер физ.ячейки или - 1 если необходимая часть
        //адресного пространства отсутствует в оперативной памяти;
        internal static extern int osTranslateAddress2(int nProcess, int nSegment, int nOffset, int nOperationType);
        
        [DllImport("MathLibrary.dll")]
        /*
            5. Функции ОС, управление вводом / выводом - прототипы функций, которые
            необходимо реализовать согласно варианту :
        */

        //5.1  - запись данных из оперативной
        //памяти в указанный файл, nProcess - номер процесса(0 - 99),
        //вызвавший метод(255 - система), fileName - имя файла(не более
        //20 символов), virtMemBuffer - адрес буфера в адресном
        //пространстве процесса, если вызывается от имени системы -
        //virtMemBuffer указывает на физ.память, count - длина буфера на
        //запись, offset - позиция в файле, с которой необходимо
        //осуществлять запись, возвращает 1 - если успех - 1 - если ошибка;
        internal static extern int osWriteFile(int nProcess, char[] fileName, int virtMemBuffer, int count, int offset);
        
        [DllImport("MathLibrary.dll")]
        //5.2  - запись данных в файл из указанного внешнего буфера,
        //fileName - имя файла(не более 20 символов), lpBuffer - адрес
        //буфера с данными, count - длина буфера на запись, возвращает 1 -
        //если успех - 1 - если ошибка;
        internal static extern int osWriteExternFile(char[] fileName, Byte[] lpBuffer, int count);
        
        [DllImport("MathLibrary.dll")]
        //5.3  - чтение из файла данных в
        //оперативную память, nProcess - номер процесса(0 - 99), вызвавший
        //метод(255 - система), fileName - имя файла(не более 20 символов),
        //virtMemBuffer - адрес буфера в адресном пространстве процесса,
        //если вызывается от имени системы - virtMemBuffer указывает на
        //физ.память, count - длина буфера на чтение, offset - позиция в
        //файле, с которой необходимо осуществлять чтение, возвращает
        //количество прочитанных символов - 1 - если ошибка
        internal static extern int osReadFile(int nProcess, char[] fileName, int virtMemBuffer, int count, int offset);
        
        [DllImport("MathLibrary.dll")]
        //5.4  - чтение из файла данных в указанный внешний буфер,
        //fileName - имя файла(не более 20 символов), lpBuffer - адрес
        //буфера с данными, count - длина буфера на для данных, возвращает
        //количество прочитанных символов - 1 - если ошибка;
        internal static extern int osReadExternFile(char[] fileName, Byte[] lpBuffer, int count);
        
        [DllImport("MathLibrary.dll")]
        //5.5  - удаление
        //файла, nProcess - номер процесса(0 - 99), вызвавший метод(255 -
        //система), fileName - имя файла(не более 20 символов), возвращает
        //1 - если успешно - 1 - если ошибка.
        internal static extern int osDeleteFile(int nProcess, char[] fileName);
    }
}
