                      #include <QtCore>
#include <QtGui>
#include <QtXml>

#include <stdexcept>
#include <climits>

#include "Common/BasicExceptions.hpp"

#include "GUI/Client/FilesPanel.hpp"
#include "GUI/Client/LibrariesPanel.hpp"
#include "GUI/Client/InvalidValue.hpp"
#include "GUI/Client/HostListPanel.hpp"
#include "GUI/Client/UnknownTypeException.hpp"

#include "GUI/Client/GraphicalOption.hpp"

using namespace CF::Common;
using namespace CF::GUI::Client;

GraphicalOption::GraphicalOption(OptionType::Type type)
{
  switch(type)
  {
    // if type valueWidget is a bool
  case OptionType::TYPE_BOOL:
    {
      QCheckBox * checkBox = new QCheckBox();
      checkBox->setCheckState(Qt::Unchecked);
      m_valueWidget = checkBox;
      break;
    }

    // if type valueWidget is a string
  case OptionType::TYPE_STRING:
    m_valueWidget = new QLineEdit();
    break;

    // if type valueWidget is a double
  case OptionType::TYPE_DOUBLE:
    {
      QDoubleValidator * validator;
      m_valueWidget = new QLineEdit();
      validator = new QDoubleValidator(m_valueWidget);
      validator->setNotation(QDoubleValidator::ScientificNotation);
      ((QLineEdit *)m_valueWidget)->setValidator(validator);
    }
    break;

    // if type valueWidget is an int
  case OptionType::TYPE_INT:
    m_valueWidget = new QSpinBox();
    ((QSpinBox *)m_valueWidget)->setRange(INT_MIN, INT_MAX);
    break;

    // if type valueWidget is an unsigned int
  case OptionType::TYPE_UNSIGNED_INT:
    m_valueWidget = new QSpinBox();
    // INT_MAX (not UINT_MAX) because parameter type is "int" (not "unsigned int")
    ((QSpinBox *)m_valueWidget)->setRange(0, INT_MAX);
    break;

    // if type valueWidget is a files list
  case OptionType::TYPE_FILES:
    m_valueWidget = new FilesPanel(true, QStringList(), true);
    break;

    // if type valueWidget is a library list
  case OptionType::TYPE_LIBRARIES:
    m_valueWidget = new LibrariesPanel();
    break;

    // if type valueWidget is a string
  case OptionType::TYPE_PATH:
    m_valueWidget = new QLineEdit();
    break;


    //    case OptionType::TYPE_HOST_LIST:
    //      m_valueWidget = new HostListPanel();
    //      break;

  default:
    throw UnknownTypeException(FromHere(), "Uknowmn option type");
  }

  m_name = new QLabel();

  m_type = type;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GraphicalOption::~GraphicalOption()
{
  delete m_name;
  delete m_valueWidget;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QString GraphicalOption::getName() const
{
  return m_name->text();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GraphicalOption::setName(const QString & name)
{
  m_name->setText(name);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QVariant GraphicalOption::getValue() const
{
  QVariant value;

  /// @todo TQ: handle the NO_TYPE in the switch

  switch(m_type)
  {
    // if type valueWidget is a bool
  case OptionType::TYPE_BOOL:
    value = ((QCheckBox *) m_valueWidget)->checkState() == Qt::Checked;
    break;

    // if type valueWidget is a string
  case OptionType::TYPE_STRING:
    value = ((QLineEdit *) m_valueWidget)->text();
    break;

    // if type valueWidget is an int
  case OptionType::TYPE_INT:
    value = ((QSpinBox *) m_valueWidget)->value();
    break;

    // if type valueWidget is an unsigned int
  case OptionType::TYPE_UNSIGNED_INT:
    value = ((QSpinBox *) m_valueWidget)->value();
    break;

    // if type valueWidget is a double
  case OptionType::TYPE_DOUBLE:
    value = ((QLineEdit *) m_valueWidget)->text();
    //    value = ((QDoubleSpinBox *) this->valueWidget)->value();
    break;

    // if type valueWidget is a files list
  case OptionType::TYPE_FILES:
    value = ((FilesPanel *) m_valueWidget)->getFilesList();
    break;

    // if type valueWidget is a library list
  case OptionType::TYPE_LIBRARIES:
    value = ((LibrariesPanel *) m_valueWidget)->getFilesList();
    break;

    // if type valueWidget is a string
  case OptionType::TYPE_PATH:
    value = ((QLineEdit *) m_valueWidget)->text();
    break;

      // if type valueWidget is a selectable item list
//    case OptionType::TYPE_HOST_LIST:
//      value = ((HostListPanel *) m_valueWidget)->getDocument().toString();
//      break;

  default:
      throw ShouldNotBeHere(FromHere(), "GraphicalOption::getValue()");

  }

  return value;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QString GraphicalOption::getValueString() const
{
//  if(m_type == TYPE_FILES || m_type == TYPE_LIBRARIES)
//    return this->getValue().toStringList().join(" ");

  return this->getValue().toString();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

OptionType::Type GraphicalOption::getType() const
{
  return m_type;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GraphicalOption::setValue(const QVariant & newValue)
{
  bool ok; // used to validate conversions

  /// @todo TQ: handle the NO_TYPE in the switch

  switch(m_type)
  {
    // if the valueWidget is a bool
  case OptionType::TYPE_BOOL:
    {
      bool val = newValue.toBool();
      ((QCheckBox *) m_valueWidget)->setCheckState(val ? Qt::Checked : Qt::Unchecked);
      break;
    }

    // if the valueWidget is a string
  case OptionType::TYPE_STRING:
    ((QLineEdit *) m_valueWidget)->setText(newValue.toString());
    break;

    // if the valueWidget is an int
  case OptionType::TYPE_INT:
    {
      int val = 0;

      if(!newValue.toString().isEmpty())
      {
        val = newValue.toInt(&ok);

        if(!ok) // if ok is false, the conversion failed
          throw InvalidValue(FromHere(), "Failed to convert to an integer");
      }

      ((QSpinBox *) m_valueWidget)->setValue(val);
      break;
    }

    // if the valueWidget if an unsigned int
  case OptionType::TYPE_UNSIGNED_INT:
    {
      unsigned int val = 0;

      if(!newValue.toString().isEmpty())
      {
        val = newValue.toUInt(&ok);

        if(!ok) // if ok is false, the conversion failed
          throw InvalidValue(FromHere(), "Failed to convert to an unsigned "
                                      "integer");
      }

      ((QSpinBox *) m_valueWidget)->setValue(val);
      break;
    }

    // if the valueWidget if a double
  case OptionType::TYPE_DOUBLE:
    {
      ((QLineEdit *) m_valueWidget)->setText(newValue.toString());
      //    double val = 0.0;
      //
      //    if(!newValue.toString().isEmpty())
      //    {
      //     val = newValue.toDouble(&ok);
      //
      //     if(!ok) // if ok is false, the conversion failed
      //      throw InvalidValue(FromHere(), "Failed to convert to a double");
      //    }
      //
      //    ((QDoubleSpinBox *) this->valueWidget)->setValue(val);
      break;
    }

    // if the valueWidget if a files list
    //    case OptionType::TYPE_FILES:
    //      ((FilesPanel *) m_valueWidget)->setFilesList(newValue.toStringList());
    //      break;

    // if the valueWidget if a library list
    //    case OptionType::TYPE_LIBRARIES:
    //      ((LibrariesPanel *) m_valueWidget)->setFilesList(newValue.toStringList());
    //      break;

    // if type valueWidget is a selectable item list
    //    case OptionType::TYPE_HOST_LIST:
    //    {
    //      QDomDocument doc;
    //      QString errString;
    //      QString valueString = newValue.toString();
    //      HostListPanel * panel = ((HostListPanel *) m_valueWidget);
    //      QDomNodeList childNodes;

    //      if(!valueString.isEmpty() && !doc.setContent(valueString, false, &errString))
    //        throw InvalidValueException(FromHere(), errString.toStdString());

    //      panel->setItems(doc);

    //      break;
    //    }

  default:
    throw ShouldNotBeHere(FromHere(), "GraphicalOption::setValue()");

    // if the valueWidget is a string
  case OptionType::TYPE_PATH:
    ((QLineEdit *) m_valueWidget)->setText(newValue.toString());
    break;


  }

  // if execution arrives here => no exception were thrown
  // => everything goes well => keep the value as original value
  m_originalValue = newValue;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GraphicalOption::addToLayout(QFormLayout * layout)
{
  if(layout != CFNULL)
  {
    layout->addRow(m_name, m_valueWidget);
    m_valueWidget->showMaximized();
  }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GraphicalOption::setEnabled(bool enabled)
{
  m_valueWidget->setEnabled(enabled);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool GraphicalOption::isEnabled() const
{
  return m_valueWidget->isEnabled();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GraphicalOption::setToolTip(const QString & toolTip)
{
  m_name->setToolTip(toolTip);
  m_valueWidget->setToolTip(toolTip);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool GraphicalOption::isModified() const
{
//  if(m_type == TYPE_HOST_LIST)
//    return static_cast<HostListPanel *>(m_valueWidget)->isModified();

  return m_originalValue != this->getValue();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QVariant GraphicalOption::getOrginalValue() const
{
  return m_originalValue;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QString GraphicalOption::getOrginalValueString() const
{
//  if(m_type == TYPE_FILES || m_type == TYPE_LIBRARIES)
//    return this->getOrginalValue().toStringList().join(" ");

  return this->getOrginalValue().toString();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void GraphicalOption::commit()
{
  m_originalValue = this->getValue();

//  if(m_type == TYPE_HOST_LIST)
//  {
//    HostListPanel * panel = static_cast<HostListPanel *>(m_valueWidget);
//    panel->setItems(panel->getDocument());
//  }
}
