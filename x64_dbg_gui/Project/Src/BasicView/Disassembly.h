#ifndef DISASSEMBLY_H
#define DISASSEMBLY_H

#include <QtGui>
#include <QtDebug>
#include "NewTypes.h"
#include "Bridge.h"
#include "AbstractTableView.h"
#include "QBeaEngine.h"
#include "BeaHighlight.h"

class Disassembly : public AbstractTableView
{
    Q_OBJECT
public:
    explicit Disassembly(QWidget *parent = 0);

    // Private Functions
    void paintRichText(QPainter* painter, int x, int y, int w, int h, int xinc, const QList<CustomRichText_t>* richText);

    // Reimplemented Functions
    QString paintContent(QPainter* painter, int_t rowBase, int rowOffset, int col, int x, int y, int w, int h);

    // Mouse Management
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    // Keyboard Management
    void keyPressEvent(QKeyEvent* event);

    // ScrollBar Management
    int_t sliderMovedHook(int type, int_t value, int_t delta);

    // Jumps Graphic
    int paintJumpsGraphic(QPainter* painter, int x, int y, int_t addr);

    // Function Graphic

    enum Function_t
    {
        Function_none,
        Function_start,
        Function_middle,
        Function_end
    };

    int paintFunctionGraphic(QPainter* painter, int x, int y, Function_t funcType, bool loop);

    // Instructions Management
    int_t getPreviousInstructionRVA(int_t rva, uint_t count);
    int_t getNextInstructionRVA(int_t rva, uint_t count);
    int_t getInstructionRVA(int_t index, int_t count);
    Instruction_t DisassembleAt(int_t rva);
    Instruction_t DisassembleAt(int_t rva, int_t count);

    // Selection Management
    void expandSelectionUpTo(int_t to);
    void setSingleSelection(int_t index);
    int_t getInitialSelection();
    void selectNext();
    void selectPrevious();
    bool isSelected(int_t base, int_t offset);
    bool isSelected(QList<Instruction_t>* buffer, int index);

    // Update/Reload/Refresh/Repaint
    void prepareData();

    // Public Methods
    uint_t rvaToVa(int_t rva);
    void disassembleClear();
    int_t getBase();
    int_t getSize();

signals:
    
public slots:
    void disassambleAt(int_t parVA, int_t parCIP);
    void debugStateChangedSlot(DBGSTATE state);

private:
    enum GuiState_t {NoState, MultiRowsSelectionState};
    enum GraphicDump_t {GD_Nothing, GD_FootToTop, GD_FootToBottom, GD_HeadFromTop, GD_HeadFromBottom, GD_Vert}; // GD_FootToTop = '- , GD_FootToBottom = ,- , GD_HeadFromTop = '-> , GD_HeadFromBottom = ,-> , GD_Vert = |

    typedef struct _SelectionData_t
    {
        int_t firstSelectedIndex;
        int_t fromIndex;
        int_t toIndex;
    } SelectionData_t;

    QBeaEngine* mDisasm;

    SelectionData_t mSelection;

    bool mIsLastInstDisplayed;

    GuiState_t mGuiState;

    int_t mBase;
    int_t mSize;

    int_t mCipRva;

    QList<Instruction_t> mInstBuffer;
};

#endif // DISASSEMBLY_H
