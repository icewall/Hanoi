object frmMain: TfrmMain
  Left = 257
  Top = 169
  Caption = 'Hanoi Towers'
  ClientHeight = 587
  ClientWidth = 1000
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 64
    Top = 211
    Width = 44
    Height = 13
    Caption = 'Operator'
  end
  object Label2: TLabel
    Left = 208
    Top = 211
    Width = 63
    Height = 13
    Caption = 'Pre-condition'
  end
  object Label3: TLabel
    Left = 376
    Top = 211
    Width = 34
    Height = 13
    Caption = 'Effects'
  end
  object Label5: TLabel
    Left = 528
    Top = 211
    Width = 65
    Height = 13
    Caption = 'Current state'
  end
  object Label6: TLabel
    Left = 712
    Top = 211
    Width = 46
    Height = 13
    Caption = 'End state'
  end
  object Label4: TLabel
    Left = 24
    Top = 507
    Width = 100
    Height = 13
    Caption = 'Amount of elements:'
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 1000
    Height = 209
    Align = alTop
    Caption = 'View'
    TabOrder = 0
    object Memo1: TMemo
      Left = 2
      Top = 15
      Width = 151
      Height = 192
      Align = alLeft
      TabOrder = 0
    end
    object Memo2: TMemo
      Left = 153
      Top = 15
      Width = 168
      Height = 192
      Align = alLeft
      TabOrder = 1
    end
    object Memo3: TMemo
      Left = 321
      Top = 15
      Width = 160
      Height = 192
      Align = alLeft
      TabOrder = 2
    end
    object Memo5: TMemo
      Left = 481
      Top = 15
      Width = 176
      Height = 192
      Align = alLeft
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 3
    end
    object Memo6: TMemo
      Left = 657
      Top = 15
      Width = 164
      Height = 192
      Align = alLeft
      ScrollBars = ssVertical
      TabOrder = 4
    end
  end
  object Button1: TButton
    Left = 24
    Top = 349
    Width = 153
    Height = 33
    Caption = 'Solve'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Memo7: TMemo
    Left = 280
    Top = 256
    Width = 521
    Height = 289
    ScrollBars = ssVertical
    TabOrder = 2
    Visible = False
  end
  object Button2: TButton
    Left = 24
    Top = 277
    Width = 153
    Height = 33
    Caption = 'generate'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 24
    Top = 421
    Width = 153
    Height = 33
    Caption = 'Simulate'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Edit1: TEdit
    Left = 126
    Top = 504
    Width = 97
    Height = 21
    TabOrder = 5
    Text = '3'
  end
end
