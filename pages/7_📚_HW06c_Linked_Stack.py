import streamlit as st
import redirect as rd
from homework import LinkedStack
import random

st.set_page_config(
    page_title="鏈結堆疊",
    page_icon="📚"
)

st.header("鏈結堆疊")
st.caption("Linked Stack")

input_options_method = {'manual': '手動設定', 'random': '隨機產生'}
input_options_detailed = {'detailed': '詳細顯示（包含記憶體位址）', 'normal': '僅顯示堆疊內容'}


col1, col2 = st.columns(2)

with col1:
    input_types = st.radio('input', input_options_method, format_func=lambda x: input_options_method.get(x))
with col2:
    input_detailed = st.radio('output', input_options_detailed, format_func=lambda x: input_options_detailed.get(x))

if input_types == 'manual':
    input_num = st.number_input("num", min_value=0, max_value=2**31 - 1)
    st.sidebar.markdown('''
    `num`：輸入堆疊的數字。
    ''')
else:
    col1, col2 = st.columns([1, 3], gap="medium")
    with col1:
        input_n = st.number_input("n", min_value=1, max_value=10000, value=3)
    with col2:
        input_minmax = st.slider("minmax", min_value=0, max_value=1000, value=(0, 100))

    st.sidebar.markdown('''
    `n`：要隨機輸入堆疊幾個數字。

    `minmax`：輸入堆疊的數字的最大最小值。
    ''')

acol1, acol2, _, acol3 = st.columns([2,2,4,2])

with acol1:
    if input_types == "manual":
        btn_push = st.button("Push", use_container_width=True)
    else:
        btn_push_randomly = st.button(f"Push {input_n} nums", use_container_width=True)
with acol2:
    btn_pop = st.button("Pop", type="primary", use_container_width=True)
with acol3:
    btn_empty = st.button(":violet[Empty :bomb:]", type="secondary", use_container_width=True)
    

@st.cache_resource
def init_stack():
    stack = LinkedStack()
    return stack

stack = init_stack()

def pop() -> int:
    try:
        result = stack.pop()
        if (result == -1): raise ValueError("堆疊已空")
    except ValueError as e:
        st.toast(e)
    return result

def push(el: int) -> int:
    return stack.push(el)


if (input_types == "manual"):
    if btn_push:
        push(input_num)
else:
    if btn_push_randomly:
        m, M = input_minmax
        for _ in range(input_n):
            push(random.randint(m, M))
            
if btn_pop:
    pop()
    
if btn_empty:
    while (stack.pop() != -1): pop()

code = st.code(language="css", body="", line_numbers=True)

with rd.stdout(to=code):
    detailed = True if input_detailed == "detailed" else False
    if detailed:
        stack.print_detailed_nodes()
    else:
        stack.print_nodes()

