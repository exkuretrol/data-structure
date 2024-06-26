from typing import List, Union

import pandas as pd
import streamlit as st
from homework import ShortestPath  # type: ignore

import redirect as rd
from menu import menu_with_redirect

menu_with_redirect()
st.header("最短路徑")
st.caption("Shortest Path")

sidebar_text_list = list()
sidebar_text_list.append("---")

c1 = st.container(border=True)
c2 = st.container(border=True)

input_size = c1.number_input("size", min_value=2, max_value=100, value=8, disabled=True)
sidebar_text_list.append(f"`size`：鄰接矩陣大小。")


@st.cache_resource
def init_sp(size: int):
    return ShortestPath(size)


sp = init_sp(input_size)


def set_attr(attr: str):
    attr_val = getattr(st.session_state, attr)
    set_attr = f"set_{attr}"
    setter = getattr(sp, set_attr)
    setter(attr_val)
    if attr == "directed":
        generate_random_matrix()


def get_matrix(m_type: str):
    m: List[List[int]]
    if m_type in ["weight", "distance", "vertex", "transitive closure"]:
        m = sp.get_matrix(m_type)
    return pd.DataFrame(m)


def set_matrix(m: Union[pd.DataFrame, None] = None):
    w = input_wall
    if isinstance(m, pd.DataFrame):
        m = m.to_numpy().astype(int).tolist()
    if m is None:
        if input_size == 8:
            m = [
                [0, w, w, w, w, w, w, w],
                [300, 0, w, w, w, w, w, w],
                [1000, 800, 0, w, w, w, w, w],
                [w, w, 1200, 0, w, w, w, w],
                [w, w, w, 1500, 0, 250, w, w],
                [w, w, w, 1000, w, 0, 900, 1400],
                [w, w, w, w, w, w, 0, 1000],
                [1700, w, w, w, w, w, w, 0],
            ]
        elif input_size == 6:
            m = [
                [0, 1, w, w, w, w],
                [w, 0, 1, w, w, w],
                [w, w, 0, 1, w, w],
                [w, w, w, 0, 1, w],
                [w, w, w, w, 0, 1],
                [w, w, 1, w, w, 0],
            ]
    sp.set_matrix(m)


with c1:
    # TODO: cause segmentation fault
    input_wall = st.number_input(
        "wall",
        min_value=1000,
        max_value=1000000000,
        value=99999,
        step=1000,
        key="wall",
        on_change=set_attr,
        kwargs={"attr": "wall"},
        disabled=True,
    )
    input_method_options = {
        "random": "隨機產生",
        "manual": "手動設定",
        "predefined": "讀取範例",
    }
    input_method = st.radio(
        "method",
        input_method_options,
        format_func=lambda x: input_method_options.get(x),
        index=1,
        horizontal=True,
    )
    sidebar_text_list.append(f"`wall`：被當作牆壁的數字，所有有效數值應該小於它。")
    sidebar_text_list.append(f"`method`：目前可選的動作。")

with c2:
    if input_method == "random":
        input_range = st.number_input(
            "range",
            min_value=1,
            max_value=2**31 - 1,
            value=1000,
            key="range",
            on_change=set_attr,
            kwargs={"attr": "range"},
        )
        input_threshold = st.number_input(
            "threshold",
            min_value=1,
            max_value=2**31 - 1,
            value=1000,
            key="threshold",
            on_change=set_attr,
            kwargs={"attr": "threshold"},
        )
        sidebar_text_list.append(
            f"`range`：隨機產生的數字最大值，範圍是 `[1, range]`。"
        )
        sidebar_text_list.append(
            f"`threshold`：閾（ㄩˋ）值，超過這個數字會被當作牆壁。\n\n謝謝熊建老師提醒我他念玉🙂"
        )
        sidebar_text_list.append(
            f"`directed`：是否為有向圖，如果開關打開圖為有向，反之為無向圖。"
        )
    elif input_method == "manual":
        st.info(
            """
        點兩下想編輯的框框後輸入數字，按 Enter 即可儲存。
        """,
            icon="💡",
        )
        m = get_matrix("weight")
        edited_m = st.data_editor(m)
        set_matrix(edited_m)
    elif input_method == "predefined":
        st.info(
            """
        需要先把 size 改成 8 讀取課本上的波士頓範例或者是 6 遞移封閉有向圖範例。""",
            icon="ℹ️",
        )
        button_boston = st.button(
            "讀取範例", disabled=False if input_size in [6, 8] else True
        )


if input_method == "random":
    c2.toggle(
        "Directed",
        value=False,
        on_change=set_attr,
        key="directed",
        kwargs={"attr": "directed"},
    )
    button_generate = c2.button("產生", type="primary")


def get_directed() -> bool:
    return sp.get_directed()


def generate_random_matrix():
    sp.random_weight_matrix()


if input_method == "random" and button_generate:
    generate_random_matrix()

if input_method == "predefined" and button_boston:
    set_matrix()

tab_a, tab_aa, tab_b, tab_c, tab_d, tab_e = st.tabs(
    [
        "All matrix",
        "Trace Paths",
        "Weight matrix",
        "All pairs distance",
        "All pairs trace vertex",
        "Transitive closure",
    ]
)

with tab_a:
    code = st.code(language="css", body="", line_numbers=True)
    with rd.stdout(to=code):
        sp.print()

with tab_aa:
    code = st.code(language="css", body="", line_numbers=True)
    with rd.stdout(to=code):
        sp.trace_all_paths()

with tab_b:
    m = get_matrix("weight")
    st.dataframe(m)

with tab_c:
    m = get_matrix("distance")
    st.dataframe(m)

with tab_d:
    w = getattr(st.session_state, "wall", 99999)
    st.warning(f"數字 {w} 代表沒有辦法通過，或者斷路。", icon="‼️")
    m = get_matrix("vertex")
    st.dataframe(m)

with tab_e:
    st.warning(f"數字 0 代表沒有辦法通過", icon="‼️")
    m = get_matrix("transitive closure")
    st.dataframe(m)

st.sidebar.markdown("\n\n".join(sidebar_text_list))
