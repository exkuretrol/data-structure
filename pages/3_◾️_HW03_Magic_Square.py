import streamlit as st
from homework import MagicSquare
import pandas as pd
from numpy import diag
import matplotlib
import warnings
warnings.simplefilter(action='ignore', category=UserWarning)

st.set_page_config(
    page_title="魔術方陣",
    page_icon="◾️"
)

st.header("魔術方陣")
st.caption("Magic Square")

st.sidebar.markdown('''
`n`：魔術方陣大小，目前只能輸入 ≥ 3 的奇數。

`d`：魔術方陣填數字方向。

''')

size_input = st.number_input(
    label="n", min_value=3, max_value=27, step=2, value=5, placeholder="魔術方陣大小")

direction_types_names = {'tl': '↖️ 右下至左上',
                         'tr': '↗️ ️左下至右上',
                         'bl': '↙️ 右上至左下',
                         'br': '↘️ 左上至右下'}

direction_input = st.radio(
    label='d',
    options=direction_types_names,
    format_func=lambda x: direction_types_names.get(x)
)

run = st.button("啟動", type="primary")

cmap = matplotlib.colormaps['RdYlGn']

def index_names(index):
    if (index == size_input): return "欄總和"
    return str(index)

def col_names(index):
    if (index == size_input): return "列總和"
    return str(index)
    
if run:
    ms = MagicSquare(size_input, direction_input)
    ms.run()
    df = pd.DataFrame(ms.getData())
    if (direction_input == "br" or direction_input == "tl"):
        df_alt = df.to_numpy()[:, ::-1]
        diag_sum = sum(diag(df_alt)) 
    else:
        diag_sum = sum(diag(df))
    df.loc[size_input, :] = df.sum(axis=0)
    df.loc[:, size_input] = df.sum(axis=1)

    df.loc[size_input, size_input] = diag_sum
    df.rename(index=index_names, columns=col_names, inplace=True)

    st.dataframe(df.style.format(precision=0).background_gradient(
        cmap=cmap, axis=None, vmin=1, vmax=size_input * size_input))
    
    if (direction_input == "tl" or direction_input == "br"):
        st.info(body="對角線加總為左下右上", icon="ℹ️")
    