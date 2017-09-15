#include <Python.h>
#include <windows.h>

static PyObject* mymod_MsgBox(PyObject *self, PyObject *args)
{
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;

	sts = MessageBoxA(0, command, 0, 0);

	return PyLong_FromLong(sts);
}

static PyMethodDef mymodMethods[] =
{
	{ "MsgBox",  mymod_MsgBox, METH_VARARGS, "Show message box." },
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef mymodModule =
{
	PyModuleDef_HEAD_INIT,
	"mymod",
	NULL,
	-1,
	mymodMethods
};

static PyObject* Init_mymodModule()
{
	return PyModule_Create(&mymodModule);
}

int main()
{
	PyImport_AppendInittab("mymod", Init_mymodModule);
	Py_Initialize();

	PyRun_SimpleString(R"xx(
from time import time,ctime
import mymod
print('Today is',ctime(time()))
mymod.MsgBox('Hello World')
)xx");

	PyRun_SimpleString(R"xx(
"import mymod"
def fib(n):
 a,b = 1,1
 for i in range(n-1):
  a,b = b,a+b
 return a
mymod.MsgBox(str(fib(60)))
)xx");

	Py_Finalize();
	return 0;
}
