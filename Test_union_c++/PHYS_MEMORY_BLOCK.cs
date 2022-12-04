using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test_union_c__
{
    // структура для описания состояния физ. памяти
    internal struct PHYS_MEMORY_BLOCK
    {
        int nStart; // начало блока в оперативной памяти
        int nLength; // длина блока
        int nProcess; // номер процесса (0-99), которому выделен блок (255 - система)
    }
}
