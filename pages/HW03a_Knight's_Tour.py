import pandas as pd
import streamlit as st
from homework import KnightsTour
from matplotlib import colormaps

from menu import menu_with_redirect

menu_with_redirect()
st.header("騎士巡迴")
st.caption("Knight's Tour")

size_input = st.number_input(
    label="n", min_value=4, step=1, value=10, placeholder="騎士巡迴棋盤大小"
)


random_input = st.checkbox(label="隨機起點", value=True)

st.sidebar.markdown(
    """
`n`：騎士巡迴棋盤大小。

`row`：起始列（0 開始算）

`column`：起始欄（0 開始算）
"""
)

if not random_input:
    x_input = st.number_input(
        label="row", min_value=0, max_value=size_input - 1, value=0
    )
    y_input = st.number_input(
        label="column", min_value=0, max_value=size_input - 1, value=0
    )

run = st.button("啟動", type="primary")

cmap = colormaps["RdYlGn"]

if run:
    if random_input:
        k = KnightsTour(size_input)
        k.toggle_random()
    else:
        k = KnightsTour(size_input, x_input, y_input)

    result = k.run()
    df = pd.DataFrame(k.get_data())

    st.dataframe(
        df.style.format(precision=0).background_gradient(
            cmap=cmap, axis=None, vmin=1, vmax=size_input**2
        )
    )

    if not result:
        st.info(body="騎士巡迴找不到路徑", icon="ℹ️")
